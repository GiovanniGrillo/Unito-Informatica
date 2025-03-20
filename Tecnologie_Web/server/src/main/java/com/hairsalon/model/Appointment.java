// server/src/main/java/com/hairsalon/model/Appointment.java
package com.hairsalon.model;

import jakarta.persistence.*;
import lombok.Data;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

@Data
@Entity
@Table(name = "appuntamenti")
public class Appointment {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ManyToOne
    @JoinColumn(name = "cliente_id", nullable = false)
    private Client client;
    
    @ManyToMany
    @JoinTable(
        name = "appuntamento_servizi",
        joinColumns = @JoinColumn(name = "appuntamento_id"),
        inverseJoinColumns = @JoinColumn(name = "servizio_id")
    )
    private List<Service> selectedServices = new ArrayList<>();
    
    @Column(name = "orario_appuntamento", nullable = false)
    private LocalDateTime appointmentTime;
    
    @Column(name = "orario_fine", nullable = false)
    private LocalDateTime endTime;
    
    @Enumerated(EnumType.STRING)
    @Column(name = "stato", nullable = false)
    private AppointmentStatus status = AppointmentStatus.BOOKED;
    
    @Column(name = "note_aggiuntive", length = 1000)
    private String additionalNotes;
    
    @Column(name = "creato_il")
    private LocalDateTime createdAt;
    
    @Column(name = "aggiornato_il")
    private LocalDateTime updatedAt;
    
    @PrePersist
    protected void onCreate() {
        createdAt = LocalDateTime.now();
        updatedAt = LocalDateTime.now();
    }
    
    @PreUpdate
    protected void onUpdate() {
        updatedAt = LocalDateTime.now();
    }
    
    public enum AppointmentStatus {
        BOOKED,
        CONFIRMED,
        IN_PROGRESS,
        COMPLETED,
        CANCELLED,
        NO_SHOW
    }
}