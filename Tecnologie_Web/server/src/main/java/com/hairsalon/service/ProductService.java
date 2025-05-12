package com.hairsalon.service;

import com.hairsalon.model.Product;
import com.hairsalon.repository.ProductRepository;
import jakarta.annotation.PostConstruct;
import org.springframework.stereotype.Service;
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
        Product product1 = new Product();
        product1.setName("Shampoo Idratante");
        product1.setDescription("Shampoo delicato per uso quotidiano con estratti naturali");
        product1.setPrice(15.99f);
        product1.setAvailableQuantity(50);
        product1.setCategory("Shampoo Donna");
        product1.setImageUrl("/img/products/shampoo_idratante.webp");
        productRepository.save(product1);
        
        Product product2 = new Product();
        product2.setName("Balsamo Riparatore");
        product2.setDescription("Balsamo intensivo per capelli secchi e danneggiati");
        product2.setPrice(18.50f);
        product2.setAvailableQuantity(40);
        product2.setCategory("Balsamo Donna");
        product2.setImageUrl("/img/products/balsamo_riparatore.webp");
        productRepository.save(product2);
        
        Product product3 = new Product();
        product3.setName("Maschera Nutriente");
        product3.setDescription("Trattamento profondo per capelli danneggiati");
        product3.setPrice(22.99f);
        product3.setAvailableQuantity(30);
        product3.setCategory("Cura Capelli Donna");
        product3.setImageUrl("/img/products/maschera_nutriente.webp");
        productRepository.save(product3);
        
        Product product4 = new Product();
        product4.setName("Gel Modellante");
        product4.setDescription("Gel modellante per uno styling definito e di lunga durata");
        product4.setPrice(25.0f);
        product4.setAvailableQuantity(25);
        product4.setCategory("Gel/Cera Uomo");
        product4.setImageUrl("/img/products/gel_modellante.webp");
        productRepository.save(product4);
        
        Product product5 = new Product();
        product5.setName("Spray Protettivo");
        product5.setDescription("Spray protettivo dal calore per prevenire danni durante lo styling");
        product5.setPrice(32.50f);
        product5.setAvailableQuantity(20);
        product5.setCategory("Cura Capelli Unisex");
        product5.setImageUrl("/img/products/spray_protettivo.webp");
        productRepository.save(product5);
        
        // Prodotti aggiuntivi
        Product product6 = new Product();
        product6.setName("Olio di Argan");
        product6.setDescription("Olio nutriente per capelli secchi e crespi, ricco di vitamina E e antiossidanti");
        product6.setPrice(28.99f);
        product6.setAvailableQuantity(15);
        product6.setCategory("Cura Capelli Donna");
        product6.setImageUrl("/img/products/olio_argan.png");
        productRepository.save(product6);
        
        Product product7 = new Product();
        product7.setName("Siero Anticrespo");
        product7.setDescription("Siero leggero che elimina il crespo e aggiunge lucentezza ai capelli");
        product7.setPrice(24.50f);
        product7.setAvailableQuantity(22);
        product7.setCategory("Creme Donna");
        product7.setImageUrl("/img/products/siero_anticrespo.png");
        productRepository.save(product7);
        
        Product product8 = new Product();
        product8.setName("Shampoo Volumizzante");
        product8.setDescription("Shampoo specifico per capelli fini, aggiunge volume e corpo ai capelli");
        product8.setPrice(16.99f);
        product8.setAvailableQuantity(35);
        product8.setCategory("Shampoo Uomo");
        product8.setImageUrl("/img/products/shampoo_volumizzante.png");
        productRepository.save(product8);
        
        Product product9 = new Product();
        product9.setName("Crema Modellante");
        product9.setDescription("Crema leggera per definire i ricci e controllare i capelli ribelli");
        product9.setPrice(19.99f);
        product9.setAvailableQuantity(18);
        product9.setCategory("Creme Unisex");
        product9.setImageUrl("/img/products/crema_modellante.webp");
        productRepository.save(product9);
        
        Product product10 = new Product();
        product10.setName("Balsamo Senza Risciacquo");
        product10.setDescription("Balsamo senza risciacquo per idratare e districare i capelli senza appesantirli");
        product10.setPrice(21.50f);
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