package cz.muni.fi.pb162.hw02.impl;

import cz.muni.fi.pb162.hw02.SimpleHttpClient;
import cz.muni.fi.pb162.hw02.crawler.SmartCrawler;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Class that uses SimpleHttpClient to act as a crawler
 *
 * @author Ondrej Kostik
 */
public class Crawler implements SmartCrawler {
    private Map<String, List<String>> map = new HashMap<>();

    @Override
    public List<String> crawl(String url) {
        String page = "";
        try {
            page = new SimpleHttpClient().get(url);
            map.put(url, new ArrayList<>());
        } catch (IOException e) { // should it return empty map or key : empty list
            map.put(url, new ArrayList<>());
            return map.get(url);
        }
        Matcher matcher = Pattern.compile("href=\"(.*?)\"").matcher(page);
        while (matcher.find()) {
            map.get(url).add(matcher.group(1));
        }
        return map.get(url);
    }

    @Override
    public Map<String, List<String>> crawlAll(String url) {
        if (crawl(url).size() != 0) {
            for (String value : map.get(url)) {
                if (!map.containsKey(value)) {
                    crawlAll(value);
                }
            }
        }
        return map;
    }

    @Override
    public Map<String, List<String>> crawlReverse(String url) {
        return reverseIndex(crawlAll(url));
    }

    @Override
    public Map<String, List<String>> reverseIndex(Map<String, List<String>> index) {
        Map<String, List<String>> newMap = new HashMap<>();
        for (Map.Entry<String, List<String>> entry : index.entrySet()) {
            newMap.put(entry.getKey(), new ArrayList<>());
            for (String value : entry.getValue()) {
                newMap.put(value, new ArrayList<>());
            }
        }
        for (Map.Entry<String, List<String>> entry : newMap.entrySet()) {
            for (Map.Entry<String, List<String>> indexEntry : index.entrySet()) {
                if (indexEntry.getValue().contains(entry.getKey())) {
                    entry.getValue().add(indexEntry.getKey());
                }
            }
        }
        return newMap;
    }
}