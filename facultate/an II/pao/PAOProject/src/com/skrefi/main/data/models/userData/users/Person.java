package com.skrefi.main.data.models.userData.users;

import com.skrefi.main.data.models.userData.Address;

import java.util.Objects;

public abstract class Person {
    private String firstName;
    private String lastName;
    private String emailAddress;
    private Address address;

    public Person(String firstName, String lastName, String emailAddress, Address address) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.emailAddress = emailAddress;
        this.address = address;
    }

    @Override
    public String toString() {
        return "Person{" +
                "firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                ", emailAddress='" + emailAddress + '\'' +
                ", address=" + address +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Person)) return false;
        Person that = (Person) o;
        return getFirstName().equals(that.getFirstName()) && getLastName().equals(that.getLastName()) && getEmailAddress().equals(that.getEmailAddress()) && getAddress().equals(that.getAddress());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getFirstName(), getLastName(), getEmailAddress(), getAddress());
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public String getEmailAddress() {
        return emailAddress;
    }

    public void setEmailAddress(String emailAddress) {
        this.emailAddress = emailAddress;
    }

    public Address getAddress() {
        return address;
    }

    public void setAddress(Address address) {
        this.address = address;
    }
}
