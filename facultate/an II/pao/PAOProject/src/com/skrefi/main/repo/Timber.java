package com.skrefi.main.repo;

public class Timber {
    private static Timber instance = null;

    private Timber() {}

    public static Timber getInstance() { return instance == null ? new Timber(): instance; }
}
