// server/src/main/java/com/hairsalon/repository/ProductRepository.java
package com.hairsalon.repository;

import com.hairsalon.model.Product;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import java.util.List;

@Repository
public interface ProductRepository extends JpaRepository<Product, Integer> {
    List<Product> findByCategory(String category);
}