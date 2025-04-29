# Hair Salon Website Project

## Project Overview
This project is a modern, responsive website for a hair salon called "Bellezza Naturale". The website showcases the salon's services, products, and allows customers to book appointments online. The project follows a client-server architecture with a React frontend and a Spring Boot backend for handling appointments, user authentication, and product management.

## Current Development Status

### Frontend (Implemented)
- **Home Page**: Fully implemented with carousel, "Chi Siamo" section, contact information, and image gallery
- **Services Page**: Implemented with service categories, descriptions, and pricing
- **Products Page**: Implemented with product listings, categories, and cart functionality
- **Authentication**: Login functionality with user roles (client/admin)
- **Cart Context**: Shopping cart functionality implemented with React Context API

### Backend (Implemented)
- Spring Boot project structure set up
- Database configuration with JPA
- REST API endpoints for authentication, products, and services
- Repository and service layers implemented
- Data models defined with JPA annotations
- Default data initialization for testing

## Technologies Used

### Frontend
- **React 19**: Modern UI library for building component-based interfaces
- **TypeScript**: For type-safe JavaScript development
- **Vite 6**: Fast build tool and development server
- **React Router 7**: For client-side routing
- **React Bootstrap 2**: UI component library based on Bootstrap 5
- **CSS**: Custom styling with modular CSS files
- **Context API**: For state management (auth, cart)

### Backend
- **Spring Boot 3.4**: Java-based framework for building web applications
- **Spring Data JPA**: For database access and ORM
- **Spring Security**: For authentication and authorization
- **MySQL**: Relational database for storing application data
- **Lombok**: For reducing boilerplate code
- **Maven**: For dependency management and build automation

## Key Features

### Home Page
- Carousel for showcasing salon highlights
- "Chi Siamo" (About Us) section introducing the salon
- Contact information
- Image gallery

### Services Page
- Comprehensive list of salon services with descriptions
- Service categories including:
  - Men's haircuts
  - Women's haircuts
  - Styling and blow-drying
  - Perms
  - Hair coloring
- Service cards with images, descriptions, and pricing
- Booking functionality (partially implemented)
  - Service selection interface
  - Appointment form UI
  - Backend integration pending

### Products Page
- Professional hair care products available for purchase
- Product categories including:
  - Shampoos and conditioners
  - Hair treatments and masks
  - Styling products
  - Heat protection products
- Product cards with images, descriptions, and pricing
- Shopping cart functionality
  - Add to cart functionality
  - Quantity selection
  - Cart display

### Authentication System
- User login functionality
- Role-based access (client/admin)
- Protected routes
- Context-based state management
