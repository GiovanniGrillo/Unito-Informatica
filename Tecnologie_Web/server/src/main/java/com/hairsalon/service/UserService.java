package com.hairsalon.service;

import com.hairsalon.model.User;
import com.hairsalon.repository.UserRepository;
import jakarta.annotation.PostConstruct;
import org.springframework.stereotype.Service;

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
                "admin",
                "Admin",
                "Demo",
                "ADMIN"
            );
            userRepository.save(admin);

            // Crea utente standard
            User user = new User(
                "user@example.com",
                "password", // In produzione usare password criptate
                "Utente",
                "Demo",
                "USER"
            );
            userRepository.save(user);
        }
    }

    public Optional<User> findByEmail(String email) {
        return userRepository.findByEmail(email);
    }

    public Optional<User> authenticate(String email, String password) {
        Optional<User> userOpt = userRepository.findByEmail(email);

        if (userOpt.isPresent()) {
            User user = userOpt.get();
            if (user.getPassword().equals(password)) {
                // Autenticazione riuscita
                return Optional.of(user);
            }
        }
        return Optional.empty();
    }

    public User save(User user) {
        return userRepository.save(user);
    }
}