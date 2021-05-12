#include "pdf/pdfgen.h"
#include "to_pdf.h"

#ifdef __cplusplus
    extern "C"
    {
#endif

static pdf_info info = {
	{.creator = "My software"},
	{.producer = "My software"},
	{.title = "My document"},
	{.author = "My name"},
	{.subject = "My subject"},
	{.date = "Today"}
};

#ifdef __cplusplus
    }
#endif


void ToPDF(char* str)
{
    pdf_doc *pdf = pdf_create(PDF_A4_WIDTH, PDF_A4_HEIGHT, &info);
    pdf_set_font(pdf, "Times-Roman");
    pdf_append_page(pdf);
    pdf_add_text(pdf, NULL, str, 15, 200, 500, PDF_BLACK);
	pdf_add_text(pdf, NULL, "Let's rub Stephen Wolfram's nose!", 15, 200, 700, PDF_BLACK);
    pdf_save(pdf, "output.pdf");
    pdf_destroy(pdf);
}
