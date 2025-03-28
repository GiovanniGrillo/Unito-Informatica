// client/src/pages/Contacts.tsx
import React, { useEffect } from "react";
import { Container, Row, Col, Card } from "react-bootstrap";
import { MapContainer, TileLayer, Marker, Popup } from "react-leaflet";
import "leaflet/dist/leaflet.css";
import L from "leaflet";

const Contacts: React.FC = () => {
    const position: [number, number] = [45.09004104958907, 7.659256380902108];

    // Fix per l'icona del marker di Leaflet
    useEffect(() => {
        // Risolve il problema dell'icona mancante
        delete L.Icon.Default.prototype._getIconUrl;
        L.Icon.Default.mergeOptions({
            iconRetinaUrl: 'https://cdnjs.cloudflare.com/ajax/libs/leaflet/1.7.1/images/marker-icon-2x.png',
            iconUrl: 'https://cdnjs.cloudflare.com/ajax/libs/leaflet/1.7.1/images/marker-icon.png',
            shadowUrl: 'https://cdnjs.cloudflare.com/ajax/libs/leaflet/1.7.1/images/marker-shadow.png',
        });
    }, []);

    return (
        <Container className="my-5">
            <Row className="justify-content-center">
                <Col md={6}>
                    <Card className="p-4 shadow-lg">
                        <Card.Body>
                            <Card.Title className="text-center fw-bold fs-3">Contatti</Card.Title>
                            <Card.Text className="mt-3">
                                <strong>Email:</strong> info@bellezzanaturale.it
                            </Card.Text>
                            <Card.Text>
                                <strong>Indirizzo:</strong> Via pessinetto, 12, 10149 Torino (TO), Italia
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
                            <Popup>Elegance Hair Salon- Gio & Fabio</Popup>
                        </Marker>
                    </MapContainer>
                </Col>
            </Row>
        </Container>
    );
};

export default Contacts;