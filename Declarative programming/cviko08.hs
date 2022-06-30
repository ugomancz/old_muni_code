echo :: IO ()

echo = do
    putStrLn "Write something"
    line <- getLine
    let out = "You wrote: " ++ line
    putStrLn out

compareInputs = do
    putStrLn "Write something"
    line1 <- getLine
    putStrLn "Write another thing"
    line2 <- getLine
    let test = if line1 > line2 then line1 else line2
    let out = "The longer line was: " ++ test
    putStrLn out

--powerInput x = do
--    putStrLn "Write something you want to double"
--    line <- getLine
--    let out 
--    putStrLn out

powerhelper x y = if y == 1 then x else x ++ powerhelper x (y-1)

getInt :: IO Int
getInt = do
    num <- getLine
    let numero = (read num :: Int)
    pure numero

main :: IO ()
main = do
    putStrLn "So you wanna know if this can be a triangle, huh? Alright, gimme the numbers"
    putStrLn "Enter the length of side a"
    a <- getInt
    putStrLn "Enter the length of side b"
    b <- getInt
    putStrLn "Enter the length of side c"
    c <- getInt
    let out = if a+b>c && b+c>a && a+c>b then "Yup, that would work (probs)" else "God knows what that is, but definitely not a triangle"
    putStrLn out
