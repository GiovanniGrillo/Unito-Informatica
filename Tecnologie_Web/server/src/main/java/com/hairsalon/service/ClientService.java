// server/src/main/java/com/hairsalon/service/ClientService.java
package com.hairsalon.service;

import com.hairsalon.model.Client;
import com.hairsalon.repository.ClientRepository;
import jakarta.annotation.PostConstruct;
import org.springframework.stereotype.Service;

import java.time.LocalDate;
import java.util.List;
import java.util.Optional;

@Service
public class ClientService {

    private final ClientRepository clientRepository;
    
    public ClientService(ClientRepository clientRepository) {
        this.clientRepository = clientRepository;
    }
    
    @PostConstruct
    public void init() {
        // Inizializzazione dati clienti
        Client client1 = new Client();
        client1.setFirstName("Mario");
        client1.setLastName("Rossi");
        client1.setEmail("mario.rossi@example.com");
        client1.setPhoneNumber("3331112233");
        client1.setBirthDate(LocalDate.of(1985, 5, 15));
        client1.setNotes("Cliente abituale");
        clientRepository.save(client1);
        
        Client client2 = new Client();
        client2.setFirstName("Giulia");
        client2.setLastName("Bianchi");
        client2.setEmail("giulia.bianchi@example.com");
        client2.setPhoneNumber("3334445566");
        client2.setBirthDate(LocalDate.of(1990, 8, 22));
        clientRepository.save(client2);
        
        Client client3 = new Client();
        client3.setFirstName("Luca");
        client3.setLastName("Verdi");
        client3.setEmail("luca.verdi@example.com");
        client3.setPhoneNumber("3337778899");
        client3.setBirthDate(LocalDate.of(1978, 3, 10));
        clientRepository.save(client3);
    }
    
    public List<Client> getAllClients() {
        return clientRepository.findAll();
    }
    
    public Optional<Client> getClientById(Long id) {
        return clientRepository.findById(id);
    }
    
    public Optional<Client> getClientByEmail(String email) {
        return clientRepository.findByEmail(email);
    }
    
    public List<Client> getClientsByLastName(String lastName) {
        return clientRepository.findByLastName(lastName);
    }
    
    public List<Client> getClientsByRegistrationDateAfter(LocalDate date) {
        return clientRepository.findByRegistrationDateAfter(date);
    }
    

    
    public Client saveClient(Client client) {
        return clientRepository.save(client);
    }
    
    public void deleteClient(Long id) {
        clientRepository.deleteById(id);
    }
}