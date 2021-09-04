#include <fcntl.h>
#include <unistd.h>
#include <system_error>
#include <cassert>
#include <string>
#include <utility>

/* In POSIX systems, opening a file or a file-like resource gives us
 * a «file descriptor», a small number that can be passed to system
 * calls such as ‹read› or ‹write›. The descriptor must be closed
 * when it is no longer needed, by calling ‹close› on it exactly
 * once (it is important not to close the same descriptor twice).
 * Write a class which safely wraps a file descriptor so that we
 * can't accidentally lose it or close it twice.
 *
 * It should be possible to move-construct and move-assign file
 * descriptors. A new valid descriptor can be created in 2 ways: by
 * calling ‹fd::open( "file", flags )› or ‹fd::dup( raw_fd )› where
 * ‹flags› and ‹raw_fd› are both ‹int›. Use POSIX functions ‹open›
 * and ‹dup› to implement this. Run ‹man 2 open› and ‹man 2 dup› on
 * ‹aisa› for details about these POSIX functions.
 *
 * Add methods ‹read› and ‹write› to the ‹fd› class, the first will
 * simply take an integer, read the given number of bytes and return
 * an ‹std::string›. The latter will take an ‹std::string› and write
 * it into the descriptor. Again see ‹man 2 read› and ‹man 2 write›
 * on ‹aisa› for advice.
 *
 * If ‹open›, ‹read› or ‹write› fails, throw ‹std::system_error›.
 * Attempting to call ‹read› or ‹write› on an invalid descriptor
 * (one that was default-constructed or already closed) should throw
 * ‹std::invalid_argument›. */

class fd {
private:
    int descriptor = -1;
public:
    fd() = default;

    fd(const char *path, int flags) noexcept : descriptor(::open(path, flags)) {}

    fd(fd &&other) noexcept: descriptor(std::exchange(other.descriptor, -1)) {}

    fd(const fd &other) = default;

    fd &operator=(const fd &) = default;

    fd &operator=(fd &&other) noexcept {
        close();
        descriptor = std::exchange(other.descriptor, -1);
        return *this;
    }

    ~fd() {
        close();
    }

    void close() {
        ::close(descriptor);
        descriptor = -1;
    }

    static fd open(const char *path, int flags) noexcept {
        return fd(path, flags);
    }

    static fd dup(const int other_descriptor) noexcept {
        fd new_fd{};
        new_fd.descriptor = ::dup(other_descriptor);
        return new_fd;
    }

    std::string read(int length) const {
        if (descriptor < 0) {
            throw std::invalid_argument("Invalid argument.");
        }
        char buf[length];
        int read_result = ::read(descriptor, buf, length);
        if (read_result < 0) {
            throw std::system_error();
        }
        return std::string(buf, read_result == 0 ? 0 : sizeof(buf));
    }

    void write(const std::string &input) const {
        if (::write(descriptor, input.c_str(), input.size()) < 0) {
            throw std::system_error();
        }
    }
};

int main()
{
    using namespace std::literals;
    int fd_0 = ::open( "/dev/null", O_WRONLY );
    assert( fd_0 >= 0 );
    ::close( fd_0 );

    fd null = fd::open( "/dev/null", O_WRONLY );
    fd zero = fd::open( "/dev/zero", O_RDONLY );
    fd rand = fd::open( "/dev/urandom", O_RDONLY );
    fd std_in = fd::dup( 0 );

    int caught = 0;

    try { null.read( 10 ); }
    catch ( std::system_error & ) { ++ caught; }
    assert( caught == 1 );

    assert( zero.read( 5 ) == "\0\0\0\0\0"s );
    assert( rand.read( 5 ) != "\0\0\0\0\0"s );

    null = fd::open( "/dev/null", O_RDWR );
    assert( null.read( 5 ).empty() );

    {
        null.write( "nope" );
        zero.close();
        fd x = std::move( null );

        try { zero.read( 10 ); }
        catch ( std::invalid_argument & ) { ++ caught; }
        assert( caught == 2 );

        try { null.read( 10 ); }
        catch ( std::invalid_argument & ) { ++ caught; }
        assert( caught == 3 );
    }

    {
        fd n2;
        {
            fd n1 = fd::open( "/dev/null", O_WRONLY );
            n1.close();
            n2 = fd::open( "/dev/null", O_WRONLY );
        }
        n2.write( "foo" );
    }

    {
        ::close( ::open( "g1_fd.out", O_CREAT, 0666 ) );
        fd file_out = fd::open( "g1_fd.out", O_WRONLY );
        file_out.write( "hello world\n" );
        fd file_in = fd::open( "g1_fd.out", O_RDONLY );
        ::unlink( "g1_fd.out" );
        assert( file_in.read( 5 ) == "hello" );
    }

    assert( ::open( "/dev/null", O_WRONLY ) == fd_0 );
}
