// server/src/main/java/com/hairsalon/service/UserService.java
package com.hairsalon.service;

import com.hairsalon.model.User;
import com.hairsalon.repository.UserRepository;
import jakarta.annotation.PostConstruct;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.util.Optional;

@Service
public class UserService {

    private final UserRepository userRepository;

    public UserService(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    @PostConstruct
    public void init() {
        // Inizializzazione utenti di default
        if (userRepository.count() == 0) {
            // Crea utente admin
            User admin = new User(
                "admin@example.com",
                "admin", // In produzione usare password criptate
                "Admin Demo",
                "ADMIN"
            );
            userRepository.save(admin);

            // Crea utente client
            User client = new User(
                "client@example.com",
                "password", // In produzione usare password criptate
                "Cliente Demo",
                "CLIENT"
            );
            userRepository.save(client);
        }
    }

    public Optional<User> findByEmail(String email) {
        return userRepository.findByEmail(email);
    }

    public Optional<User> authenticate(String email, String password) {
        Optional<User> userOpt = userRepository.findByEmail(email);
        
        if (userOpt.isPresent()) {
            User user = userOpt.get();
            // In produzione, confrontare password criptate
            if (user.getPassword().equals(password)) {
                // Aggiorna l'ultimo accesso
                user.setLastLogin(LocalDateTime.now());
                userRepository.save(user);
                return Optional.of(user);
            }
        }
        
        return Optional.empty();
    }

    public User save(User user) {
        return userRepository.save(user);
    }
}