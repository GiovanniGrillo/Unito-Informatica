// server/src/main/java/com/hairsalon/repository/AppointmentRepository.java
package com.hairsalon.repository;

import com.hairsalon.model.Appointment;
import com.hairsalon.model.Appointment.AppointmentStatus;
import com.hairsalon.model.Client;
// Stylist import removed
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;

import java.time.LocalDateTime;
import java.util.List;

@Repository
public interface AppointmentRepository extends JpaRepository<Appointment, Long> {
    List<Appointment> findByClient(Client client);
    // Stylist-related method removed
    List<Appointment> findByStatus(AppointmentStatus status);
    
    List<Appointment> findByAppointmentTimeBetween(LocalDateTime start, LocalDateTime end);
    
    List<Appointment> findByClientAndAppointmentTimeAfter(Client client, LocalDateTime dateTime);
    // Stylist-related method removed
    
    // Stylist-related query method removed
    
    @Query("SELECT a FROM Appointment a JOIN a.selectedServices s WHERE s.id = :serviceId")
    List<Appointment> findByServiceId(Long serviceId);
}