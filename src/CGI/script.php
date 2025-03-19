<?php

// Récupérer la valeur de "name" depuis QUERY_STRING (via $_GET)
$name = isset($_GET['name']) ? $_GET['name'] : "Inconnu";

// Générer une page HTML simple
echo "<!DOCTYPE html>\n";
echo "<html lang=\"en\">\n";
echo "<head>\n";
echo "    <meta charset=\"UTF-8\">\n";
echo "    <title>Bonjour</title>\n";
echo "</head>\n";
echo "<body>\n";
echo "    <h1>Bonjour, " . htmlspecialchars($name) . " !</h1>\n";
echo "    <p>La QUERY_STRING reçue est : " . htmlspecialchars($_SERVER['QUERY_STRING']) . "</p>\n";
echo "</body>\n";
echo "</html>\n";
?>