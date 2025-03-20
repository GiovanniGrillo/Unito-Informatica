// server/src/main/java/com/hairsalon/model/Client.java
package com.hairsalon.model;

import jakarta.persistence.*;
import lombok.Data;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

@Data
@Entity
@Table(name = "clienti")
public class Client {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "nome", nullable = false)
    private String firstName;
    
    @Column(name = "cognome", nullable = false)
    private String lastName;
    
    @Column(name = "email", unique = true)
    private String email;
    
    @Column(name = "telefono")
    private String phoneNumber;
    
    @Column(name = "data_nascita")
    private LocalDate birthDate;
    
    @ElementCollection
    @CollectionTable(name = "preferenze_cliente", joinColumns = @JoinColumn(name = "cliente_id"))
    @Column(name = "preferenza")
    private List<String> preferences = new ArrayList<>();
    
    @Column(name = "note", length = 1000)
    private String notes;
    
    @Column(name = "data_registrazione")
    private LocalDate registrationDate;
    
    @PrePersist
    protected void onCreate() {
        if (registrationDate == null) {
            registrationDate = LocalDate.now();
        }
    }
}