package cz.muni.fi.pb162.hw01.impl;

import cz.muni.fi.pb162.hw01.DefaultPortResolver;
import cz.muni.fi.pb162.hw01.url.SmartUrl;

import java.util.ArrayList;
import java.util.Arrays;

/**
 * Url class serves to get different parts of a URL address and compare two URLs
 * using their canonical version to check if they are equal.
 *
 * @author Ondrej Kostik
 */
public class Url implements SmartUrl {
    private String url;

    Url(String string) {
        this.url = string;
    }

    @Override
    public String getAsRawString() {
        return url;
    }

    @Override
    public String getHost() {
        String[] urlArray = url.split("/", 4);
        String[] hostAndPortArray = urlArray[2].split(":");
        if (hostAndPortArray.length == 2) {
            DefaultPortResolver truePort = new DefaultPortResolver();
            if (getPort() != truePort.getPort(getProtocol())) {
                return urlArray[2];
            }
            return hostAndPortArray[0];
        }
        String[] hostArray = hostAndPortArray[0].split(".");
        if (hostArray.length == 1) {
            return "";
        }
        return hostAndPortArray[0];
    }

    @Override
    public String getProtocol() {
        String[] protocolArray = url.split("://");
        if (protocolArray.length >= 1) {
            return protocolArray[0];
        }
        return "";
    }

    @Override
    public int getPort() {
        String[] urlArray = url.split("/", 4);
        String[] portArray = urlArray[2].split(":");
        if (portArray.length == 2) {
            return Integer.parseInt(portArray[1]);
        }
        DefaultPortResolver portResolver = new DefaultPortResolver();
        String protocol = getProtocol();
        if (protocol.equals("")) {
            System.out.println("No protocol found, possibly invalid URL, returning invalid port");
            return -1;
        }
        return portResolver.getPort(protocol);
    }

    /**
     * Helper method to get pathArray used in getPath()
     *
     * @return array of String representing the "path" part of URL
     */
    private String[] getPathArray() {
        String[] urlArray;
        String[] pathArray;
        if (!getQuery().equals("")) {
            urlArray = url.split("\\?");
        } else if (!getFragment().equals("")) {
            urlArray = url.split("#");
        } else {
            urlArray = url.split("/");
        }
        if (urlArray.length == 2) {
            pathArray = urlArray[0].split("/");
        } else {
            pathArray = urlArray;
        }
        return pathArray;
    }

    @Override
    public String getPath() {
        String[] pathArray = getPathArray();
        ArrayList<String> finalPathArray = new ArrayList<String>();
        for (int i = 3; i < pathArray.length; i++) {
            if (pathArray[i].equals("..")) {
                if (finalPathArray.size() == 0) {
                    return "";
                }
                finalPathArray.remove(finalPathArray.size() - 1);
                continue;
            }
            if (!pathArray[i].equals(".")) {
                finalPathArray.add(pathArray[i]);
            }
        }
        if (finalPathArray.size() == 0) {
            return "";
        }
        return String.join("/", finalPathArray);
    }

    @Override
    public String getFragment() {
        String[] fragmentArray = url.split("#");
        if (fragmentArray.length == 2) {
            return fragmentArray[fragmentArray.length - 1];
        }
        return "";
    }

    @Override
    public String getQuery() {
        String[] urlArray = url.split("\\?");
        if (urlArray.length == 1) {
            return "";
        }
        String[] almostQueryArray = urlArray[urlArray.length - 1].split("#");
        String[] queryArray = almostQueryArray[0].split("&"); // array of query elements
        Arrays.sort(queryArray);
        return String.join("&", queryArray);
    }

    @Override
    public String getAsString() {
        if (url == null) {
            return "";
        }
        String protocol = getProtocol();
        if (protocol.equals("")) {
            return "";
        }
        String partUrl = String.format("%s://%s", protocol, getHost());
        String path = getPath();
        String query = getQuery();
        String fragment = getFragment();
        if (!path.equals("")) {
            partUrl = String.join("/", partUrl, path);
        }
        if (!query.equals("")) {
            partUrl = String.join("?", partUrl, query);
        }
        if (!fragment.equals("")) {
            partUrl = String.join("#", partUrl, fragment);
        }
        return partUrl;
    }

    @Override
    public boolean isSameAs(String url) {
        Url newUrl = new Url(url);
        return isSameAs(newUrl);
    }

    @Override
    public boolean isSameAs(SmartUrl url) {
        return this.getAsString().equals(url.getAsString());
    }
}