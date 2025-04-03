// server/src/main/java/com/hairsalon/model/User.java
package com.hairsalon.model;

import jakarta.persistence.*;

@Entity
@Table(name = "users")
public class User {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(columnDefinition = "BIGINT(20) NOT NULL AUTO_INCREMENT FIRST")
    private Long id;

    @Column(name = "name", columnDefinition = "VARCHAR(255) AFTER id")
    private String name;

    @Column(name = "surname", columnDefinition = "VARCHAR(255) AFTER name")
    private String surname;

    @Column(name = "email", unique = true, nullable = false, columnDefinition = "VARCHAR(255) AFTER surname")
    private String email;

    @Column(name = "password", nullable = false, columnDefinition = "VARCHAR(255) AFTER email")
    private String password;

    @Column(name = "role", nullable = false, columnDefinition = "VARCHAR(255) AFTER password")
    private String role; // ADMIN, USER



    public User() {}

    public User(String email, String password, String name, String surname, String role) {
        this.name = name;
        this.surname = surname;
        this.email = email;
        this.password = password;
        this.role = role;
    }

    public Long getId() {
        return id;
    }
    public void setId(Long id) {
        this.id = id;
    }


    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }


    public String getSurname() {
        return surname;
    }
    public void setSurname(String surname) {
        this.surname = surname;
    }


    public String getEmail() {
        return email;
    }
    public void setEmail(String email) {
        this.email = email;
    }


    public String getPassword() {
        return password;
    }
    public void setPassword(String password) {
        this.password = password;
    }


    public String getRole() {
        return role;
    }
    public void setRole(String role) {
        this.role = role;
    }
}