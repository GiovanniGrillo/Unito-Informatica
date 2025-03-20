// server/src/main/java/com/hairsalon/model/Product.java
package com.hairsalon.model;

import jakarta.persistence.*;
import lombok.Data;
import java.math.BigDecimal;

@Data
@Entity
@Table(name = "prodotti")
public class Product {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(name = "nome", nullable = false)
    private String name;

    @Column(name = "descrizione", length = 1000)
    private String description;

    @Column(name = "prezzo", nullable = false)
    private BigDecimal price;

    @Column(name = "quantita_disponibile")
    private Integer availableQuantity;

    @Column(name = "categoria")
    private String category;

    @Column(name = "url_immagine")
    private String imageUrl;
}