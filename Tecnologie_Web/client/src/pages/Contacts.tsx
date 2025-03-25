// client/src/pages/Contacts.tsx
import React from "react";
import { Container, Row, Col, Card } from "react-bootstrap";
import { MapContainer, TileLayer, Marker, Popup } from "react-leaflet";
import "leaflet/dist/leaflet.css";

const Contacts: React.FC = () => {
    const position: [number, number] = [45.09004104958907, 7.659256380902108]; // Coordinate per Torino, Cuneo

    // @ts-ignore
    // @ts-ignore
    return (
        <Container className="my-5">
            <Row className="justify-content-center">
                <Col md={6}>
                    <Card className="p-4 shadow-lg">
                        <Card.Body>
                            <Card.Title className="text-center fw-bold fs-3">Contatti</Card.Title>
                            <Card.Text className="mt-3">
                                <strong>Email:</strong> info@efabegio_hs.com
                            </Card.Text>
                            <Card.Text>
                                <strong>Indirizzo:</strong> Via Roma 15, 10100 Torino (TO), Italia
                            </Card.Text>
                            <Card.Text>
                                <strong>Telefono:</strong> +39 011 234567
                            </Card.Text>
                        </Card.Body>
                    </Card>
                </Col>
                <Col md={6} className="mt-4 mt-md-0">
                    <MapContainer center={position} zoom={15} style={{ height: "300px", width: "100%" }}>
                        <TileLayer
                            url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
                            attribution='&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
                        />
                        <Marker position={position}>
                            <Popup>Elegance Hair Salon - Saluzzo, Cuneo</Popup>
                        </Marker>
                    </MapContainer>
                </Col>
            </Row>
        </Container>
    );
};

export default Contacts;