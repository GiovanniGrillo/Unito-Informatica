// server/src/main/java/com/hairsalon/repository/ClientRepository.java
package com.hairsalon.repository;

import com.hairsalon.model.Client;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;
import java.time.LocalDate;
import java.util.List;
import java.util.Optional;

@Repository
public interface ClientRepository extends JpaRepository<Client, Long> {
    Optional<Client> findByEmail(String email);
    List<Client> findByLastName(String lastName);
    List<Client> findByRegistrationDateAfter(LocalDate date);
    
    @Query("SELECT c FROM Client c JOIN c.preferences p WHERE p = :preference")
    List<Client> findByPreference(String preference);
}