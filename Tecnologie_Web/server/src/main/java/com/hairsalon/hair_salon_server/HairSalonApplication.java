package com.hairsalon.hair_salon_server;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.domain.EntityScan;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.data.jpa.repository.config.EnableJpaRepositories;

@SpringBootApplication
@ComponentScan(basePackages = {"com.hairsalon"})
@EntityScan("com.hairsalon.model")
@EnableJpaRepositories("com.hairsalon.repository")
public class HairSalonApplication {

    public static void main(String[] args) {
        SpringApplication.run(HairSalonApplication.class, args);
    }
}