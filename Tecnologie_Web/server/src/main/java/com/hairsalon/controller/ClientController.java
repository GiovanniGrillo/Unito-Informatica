// server/src/main/java/com/hairsalon/controller/ClientController.java
package com.hairsalon.controller;

import com.hairsalon.model.Client;
import com.hairsalon.service.ClientService;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDate;
import java.util.List;

@RestController
@RequestMapping("/clients")
@CrossOrigin(origins = "http://localhost:5173")
public class ClientController {

    private final ClientService clientService;

    public ClientController(ClientService clientService) {
        this.clientService = clientService;
    }

    @GetMapping("")
    public ResponseEntity<List<Client>> clients(
            @RequestParam(required = false) String lastName,
            @RequestParam(required = false) String email,
            @RequestParam(required = false) @DateTimeFormat(iso = DateTimeFormat.ISO.DATE) LocalDate registeredAfter) {
        
        if (lastName != null) {
            return ResponseEntity.ok(clientService.getClientsByLastName(lastName));
        }
        if (email != null) {
            return clientService.getClientByEmail(email)
                    .map(client -> ResponseEntity.ok(List.of(client)))
                    .orElse(ResponseEntity.ok(List.of()));
        }
        if (registeredAfter != null) {
            return ResponseEntity.ok(clientService.getClientsByRegistrationDateAfter(registeredAfter));
        }
        
        return ResponseEntity.ok(clientService.getAllClients());
    }

    @GetMapping("/{id}")
    public ResponseEntity<Client> getClient(@PathVariable Long id) {
        return clientService.getClientById(id)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.notFound().build());
    }

    @PostMapping("")
    public ResponseEntity<Client> createClient(@RequestBody Client client) {
        return ResponseEntity.ok(clientService.saveClient(client));
    }

    @PutMapping("/{id}")
    public ResponseEntity<Client> updateClient(@PathVariable Long id, @RequestBody Client client) {
        return clientService.getClientById(id)
                .map(existingClient -> {
                    client.setId(id);
                    return ResponseEntity.ok(clientService.saveClient(client));
                })
                .orElse(ResponseEntity.notFound().build());
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> deleteClient(@PathVariable Long id) {
        return clientService.getClientById(id)
                .map(client -> {
                    clientService.deleteClient(id);
                    return ResponseEntity.ok().<Void>build();
                })
                .orElse(ResponseEntity.notFound().build());
    }
}