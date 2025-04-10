package com.hairsalon.model;

import jakarta.persistence.*;

@Entity
@Table(name = "products")
public class Product {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    @Column(name = "name", nullable = false)
    private String name;

    @Column(name = "description", length = 1000)
    private String description;

    @Column(name = "price", nullable = false)
    private float price;

    @Column(name = "available_quantity")
    private Integer availableQuantity;

    @Column(name = "category")
    private String category;

    @Column(name = "image_url")
    private String imageUrl;

    public Product() {}

    public Product(String name, float price) {
        this.name = name;
        this.price = price;
    }

    public Product(String name, String description, float price, 
                  Integer availableQuantity, String category, String imageUrl) {
        this.name = name;
        this.description = description;
        this.price = price;
        this.availableQuantity = availableQuantity;
        this.category = category;
        this.imageUrl = imageUrl;
    }

    public Integer getId() {
        return id;
    }
    public void setId(Integer id) {
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


    public float getPrice() {
        return price;
    }
    public void setPrice(float price) {
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