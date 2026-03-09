SELECT Customers.CustomerName, Invoices.InvoiceID, SUM(InvoiceDetails.LineTotal) AS LineSum
FROM Invoices
INNER JOIN InvoiceDetails ON Invoices.InvoiceID = InvoiceDetails.InvoiceID
INNER JOIN Customers ON Invoices.CustomerID = Customers.CustomerID
GROUP BY Invoices.InvoiceID
ORDER BY LineSum DESC;

