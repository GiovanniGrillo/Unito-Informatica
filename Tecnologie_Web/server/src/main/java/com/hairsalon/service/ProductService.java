// server/src/main/java/com/hairsalon/service/ProductService.java
package com.hairsalon.service;

import com.hairsalon.model.Product;
import com.hairsalon.repository.ProductRepository;
import jakarta.annotation.PostConstruct;
import org.springframework.stereotype.Service;

import java.math.BigDecimal;
import java.util.List;
import java.util.Optional;

@Service
public class ProductService {

    private final ProductRepository productRepository;

    public ProductService(ProductRepository productRepository) {
        this.productRepository = productRepository;
    }
    
    @PostConstruct
    public void init() {
        // Inizializzazione dati prodotti
        Product product1 = new Product();
        product1.setName("Shampoo Professionale");
        product1.setDescription("Shampoo delicato per uso quotidiano con estratti naturali");
        product1.setPrice(new BigDecimal("15.99"));
        product1.setAvailableQuantity(50);
        product1.setCategory("Shampoo");
        product1.setImageUrl("/img/products/shampoo_idratante.webp");
        productRepository.save(product1);
        
        Product product2 = new Product();
        product2.setName("Balsamo Nutriente");
        product2.setDescription("Balsamo intensivo per capelli secchi e danneggiati");
        product2.setPrice(new BigDecimal("18.50"));
        product2.setAvailableQuantity(40);
        product2.setCategory("Balsamo");
        product2.setImageUrl("/img/products/balsamo_riparatore.webp");
        productRepository.save(product2);
        
        Product product3 = new Product();
        product3.setName("Maschera Ristrutturante");
        product3.setDescription("Trattamento profondo per capelli danneggiati");
        product3.setPrice(new BigDecimal("22.99"));
        product3.setAvailableQuantity(30);
        product3.setCategory("Trattamento");
        product3.setImageUrl("/img/products/maschera_nutriente.webp");
        productRepository.save(product3);
        
        Product product4 = new Product();
        product4.setName("Gel Modellante");
        product4.setDescription("Gel modellante per uno styling duraturo e definito");
        product4.setPrice(new BigDecimal("25.00"));
        product4.setAvailableQuantity(25);
        product4.setCategory("Styling");
        product4.setImageUrl("/img/products/gel_modellante.webp");
        productRepository.save(product4);
        
        Product product5 = new Product();
        product5.setName("Spray Protettivo");
        product5.setDescription("Spray protettivo dal calore per prevenire danni durante lo styling");
        product5.setPrice(new BigDecimal("32.50"));
        product5.setAvailableQuantity(20);
        product5.setCategory("Protezione");
        product5.setImageUrl("/img/products/spray_protettivo.webp");
        productRepository.save(product5);
    }

    public List<Product> getAllProducts() {
        return productRepository.findAll();
    }

    public Optional<Product> getProductById(Long id) {
        return productRepository.findById(id);
    }

    public List<Product> getProductsByCategory(String category) {
        return productRepository.findByCategory(category);
    }

    public Product saveProduct(Product product) {
        return productRepository.save(product);
    }

    public void deleteProduct(Long id) {
        productRepository.deleteById(id);
    }
}