// server/src/main/java/com/hairsalon/model/Product.java
package com.hairsalon.model;

import jakarta.persistence.*;
import java.math.BigDecimal;

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

    public Product() {}

    public Product(String name, BigDecimal price) {
        this.name = name;
        this.price = price;
    }

    public Product(String name, String description, BigDecimal price, 
                  Integer availableQuantity, String category, String imageUrl) {
        this.name = name;
        this.description = description;
        this.price = price;
        this.availableQuantity = availableQuantity;
        this.category = category;
        this.imageUrl = imageUrl;
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

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public BigDecimal getPrice() {
        return price;
    }

    public void setPrice(BigDecimal price) {
        this.price = price;
    }

    public Integer getAvailableQuantity() {
        return availableQuantity;
    }

    public void setAvailableQuantity(Integer availableQuantity) {
        this.availableQuantity = availableQuantity;
    }

    public String getCategory() {
        return category;
    }

    public void setCategory(String category) {
        this.category = category;
    }

    public String getImageUrl() {
        return imageUrl;
    }

    public void setImageUrl(String imageUrl) {
        this.imageUrl = imageUrl;
    }
}