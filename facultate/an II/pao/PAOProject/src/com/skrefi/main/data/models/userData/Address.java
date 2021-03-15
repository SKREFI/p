package com.skrefi.main.data.models.userData;

import java.util.Objects;

public class Address {
    private String state;
    private String city;

    private String street;

    public Address(String state, String city, String street) {
        this.state = state;
        this.city = city;
        this.street = street;
    }

    @Override
    public String toString() {
        return "Address{" +
                "state='" + state + '\'' +
                ", city='" + city + '\'' +
                ", street='" + street + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Address)) return false;
        Address address = (Address) o;
        return getState().equals(address.getState()) && getCity().equals(address.getCity()) && getStreet().equals(address.getStreet());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getState(), getCity(), getStreet());
    }

    public String getState() {
        return state;
    }

    public void setState(String state) {
        this.state = state;
    }

    public String getCity() {
        return city;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public String getStreet() {
        return street;
    }

    public void setStreet(String street) {
        this.street = street;
    }
}
