// server/src/main/java/com/hairsalon/controller/AuthController.java
package com.hairsalon.controller;

import com.hairsalon.model.User;
import com.hairsalon.service.UserService;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

@RestController
@RequestMapping("/api/auth")
@CrossOrigin(origins = "http://localhost:5173")
public class AuthController {

    private final UserService userService;

    public AuthController(UserService userService) {
        this.userService = userService;
    }

    @PostMapping("/login")
    public ResponseEntity<?> login(@RequestBody Map<String, String> credentials) {
        String email = credentials.get("email");
        String password = credentials.get("password");

        if (email == null || password == null) {
            Map<String, String> error = new HashMap<>();
            error.put("message", "Email e password sono richiesti");
            return ResponseEntity.badRequest().body(error);
        }

        Optional<User> userOpt = userService.authenticate(email, password);

        if (userOpt.isPresent()) {
            User user = userOpt.get();
            // Non inviare la password al frontend
            Map<String, Object> response = new HashMap<>();
            response.put("id", user.getId());
            response.put("name", user.getName());
            response.put("email", user.getEmail());
            response.put("role", user.getRole().toLowerCase()); // Converti in minuscolo per compatibilità con il frontend

            return ResponseEntity.ok(response);
        } else {
            Map<String, String> error = new HashMap<>();
            error.put("message", "Credenziali non valide");
            return ResponseEntity.status(401).body(error);
        }
    }
}