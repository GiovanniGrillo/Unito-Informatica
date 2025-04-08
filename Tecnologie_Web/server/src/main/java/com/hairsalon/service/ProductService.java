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
        // Initialization of product data
        Product product1 = new Product();
        product1.setName("Moisturizing Shampoo");
        product1.setDescription("Gentle shampoo for daily use with natural extracts");
        product1.setPrice(new BigDecimal("15.99"));
        product1.setAvailableQuantity(50);
        product1.setCategory("Shampoo Donna");
        product1.setImageUrl("/img/products/shampoo_idratante.webp");
        productRepository.save(product1);
        
        Product product2 = new Product();
        product2.setName("Repairing Conditioner");
        product2.setDescription("Intensive conditioner for dry and damaged hair");
        product2.setPrice(new BigDecimal("18.50"));
        product2.setAvailableQuantity(40);
        product2.setCategory("Balsamo Donna");
        product2.setImageUrl("/img/products/balsamo_riparatore.webp");
        productRepository.save(product2);
        
        Product product3 = new Product();
        product3.setName("Nourishing Mask");
        product3.setDescription("Deep treatment for damaged hair");
        product3.setPrice(new BigDecimal("22.99"));
        product3.setAvailableQuantity(30);
        product3.setCategory("Cura Capelli Donna");
        product3.setImageUrl("/img/products/maschera_nutriente.webp");
        productRepository.save(product3);
        
        Product product4 = new Product();
        product4.setName("Styling Gel");
        product4.setDescription("Modeling gel for long-lasting and defined styling");
        product4.setPrice(new BigDecimal("25.00"));
        product4.setAvailableQuantity(25);
        product4.setCategory("Gel/Cera Uomo");
        product4.setImageUrl("/img/products/gel_modellante.webp");
        productRepository.save(product4);
        
        Product product5 = new Product();
        product5.setName("Protective Spray");
        product5.setDescription("Heat protective spray to prevent damage during styling");
        product5.setPrice(new BigDecimal("32.50"));
        product5.setAvailableQuantity(20);
        product5.setCategory("Cura Capelli Unisex");
        product5.setImageUrl("/img/products/spray_protettivo.webp");
        productRepository.save(product5);
        
        // Additional products
        Product product6 = new Product();
        product6.setName("Argan Oil");
        product6.setDescription("Nourishing oil for dry and frizzy hair, rich in vitamin E and antioxidants");
        product6.setPrice(new BigDecimal("28.99"));
        product6.setAvailableQuantity(15);
        product6.setCategory("Cura Capelli Donna");
        product6.setImageUrl("/img/products/olio_argan.png");
        productRepository.save(product6);
        
        Product product7 = new Product();
        product7.setName("Anti-Frizz Serum");
        product7.setDescription("Lightweight serum that eliminates frizz and adds shine to hair");
        product7.setPrice(new BigDecimal("24.50"));
        product7.setAvailableQuantity(22);
        product7.setCategory("Creme Donna");
        product7.setImageUrl("/img/products/siero_anticrespo.png");
        productRepository.save(product7);
        
        Product product8 = new Product();
        product8.setName("Volumizing Shampoo");
        product8.setDescription("Specific shampoo for fine hair, adds volume and body to hair");
        product8.setPrice(new BigDecimal("16.99"));
        product8.setAvailableQuantity(35);
        product8.setCategory("Shampoo Uomo");
        product8.setImageUrl("/img/products/shampoo_volumizzante.png");
        productRepository.save(product8);
        
        Product product9 = new Product();
        product9.setName("Styling Cream");
        product9.setDescription("Light cream to define curls and control rebellious hair");
        product9.setPrice(new BigDecimal("19.99"));
        product9.setAvailableQuantity(18);
        product9.setCategory("Creme Unisex");
        product9.setImageUrl("/img/products/crema_modellante.webp");
        productRepository.save(product9);
        
        Product product10 = new Product();
        product10.setName("Leave-in Conditioner");
        product10.setDescription("Leave-in conditioner to moisturize and detangle hair without weighing it down");
        product10.setPrice(new BigDecimal("21.50"));
        product10.setAvailableQuantity(25);
        product10.setCategory("Balsamo Unisex");
        product10.setImageUrl("/img/products/balsamo_no_risciacquo.webp");
        productRepository.save(product10);
    }

    public List<Product> getAllProducts() {
        return productRepository.findAll();
    }

    public Optional<Product> getProductById(Integer id) {
        return productRepository.findById(id);
    }

    public List<Product> getProductsByCategory(String category) {
        return productRepository.findByCategory(category);
    }

    public Product saveProduct(Product product) {
        return productRepository.save(product);
    }

    public void deleteProduct(Integer id) {
        productRepository.deleteById(id);
    }
}