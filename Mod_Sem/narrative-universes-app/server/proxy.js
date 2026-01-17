import express from 'express';
import cors from 'cors';

const app = express();
const PORT = 3001;
const GRAPHDB_URL = 'http://localhost:7200/repositories/narrative-universes';

app.use(cors());
app.use(express.text({ type: '*/*' }));

app.post('/sparql', async (req, res) => {
    try {
        const response = await fetch(GRAPHDB_URL, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/sparql-query',
                'Accept': 'application/sparql-results+json'
            },
            body: req.body
        });

        const data = await response.json();
        res.json(data);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

app.listen(PORT, () => {
    console.log(`✅ Proxy running on http://localhost:${PORT}`);
});