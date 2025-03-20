// server/src/main/java/com/hairsalon/model/Service.java
package com.hairsalon.model;

import jakarta.persistence.*;
import lombok.Data;

import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;

@Data
@Entity
@Table(name = "servizi")
public class Service {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "nome", nullable = false)
    private String name;

    @Column(name = "descrizione", length = 1000)
    private String description;

    @Column(name = "prezzo", nullable = false)
    private BigDecimal price;

    @Column(name = "durata_minuti", nullable = false)
    private Integer durationMinutes;

    @Column(name = "livello_esperienza_richiesto")
    private String requiredExpertiseLevel;

    @ManyToMany
    @JoinTable(
        name = "servizio_prodotti",
        joinColumns = @JoinColumn(name = "servizio_id"),
        inverseJoinColumns = @JoinColumn(name = "prodotto_id")
    )
    private List<Product> requiredProducts = new ArrayList<>();

    @Column(name = "categoria")
    private String category;

    @Column(name = "url_immagine")
    private String imageUrl;
}