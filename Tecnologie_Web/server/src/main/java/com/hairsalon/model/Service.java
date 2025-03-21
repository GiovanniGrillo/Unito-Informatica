// server/src/main/java/com/hairsalon/model/Service.java
package com.hairsalon.model;

import jakarta.persistence.*;
import java.math.BigDecimal;

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

    @Column(name = "categoria")
    private String category;

    @Column(name = "url_immagine")
    private String imageUrl;
    
    public Service() {}
    
    public Service(String name, BigDecimal price, Integer durationMinutes) {
        this.name = name;
        this.price = price;
        this.durationMinutes = durationMinutes;
    }
    
    public Service(String name, String description, BigDecimal price, 
                  Integer durationMinutes, String requiredExpertiseLevel, 
                  String category, String imageUrl) {
        this.name = name;
        this.description = description;
        this.price = price;
        this.durationMinutes = durationMinutes;
        this.requiredExpertiseLevel = requiredExpertiseLevel;
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

    public Integer getDurationMinutes() {
        return durationMinutes;
    }

    public void setDurationMinutes(Integer durationMinutes) {
        this.durationMinutes = durationMinutes;
    }

    public String getRequiredExpertiseLevel() {
        return requiredExpertiseLevel;
    }

    public void setRequiredExpertiseLevel(String requiredExpertiseLevel) {
        this.requiredExpertiseLevel = requiredExpertiseLevel;
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