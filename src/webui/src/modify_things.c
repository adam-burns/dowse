
/*  Dowse - embedded WebUI based on Kore.io
 *
 *  (c) Copyright 2016 Dyne.org foundation, Amsterdam
 *  Written by Nicola Rossi <nicola@dyne.org>
 *
 * This source code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Public License as published
 * by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * This source code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * Please refer to the GNU Public License for more details.
 *
 * You should have received a copy of the GNU Public License along with
 * this source code; if not, write to:
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */
#include <webui.h>

int modify_things(struct http_request * req) {
    template_t tmpl;
	attributes_set_t attr;
    char *html_rendered;
    struct kore_buf *out;
    int len;
    http_populate_post(req);

    PARSE_PARAMETER(macaddr);
    PARSE_PARAMETER(column);
    PARSE_PARAMETER(value);

    out = kore_buf_alloc(0);
	attr=attrinit();

	if (strcmp(macaddr,"")==0) {
	     char m[1024];
	        snprintf(m,sizeof(m),"macaddr is not validated ");
	        attributes_set_t att=attrinit();
	        webui_add_error_message(&att,m);
	        err(m);
	        return show_generic_message_page(req,att);
	}
    if (strcmp(macaddr,"")==0) {
         char m[1024];
            snprintf(m,sizeof(m),"column is not validated ");
            attributes_set_t att=attrinit();
            webui_add_error_message(&att,m);
            err(m);
            return show_generic_message_page(req,att);
    }
    if (strcmp(macaddr,"")==0) {
         char m[1024];
            snprintf(m,sizeof(m),"\"value\" is not validated ");
            attributes_set_t att=attrinit();
            webui_add_error_message(&att,m);
            err(m);
            return show_generic_message_page(req,att);
    }

	/**/
    WEBUI_DEBUG;
    char sql[512];
    snprintf(sql,sizeof(sql),
            "UPDATE found set %s='%s' where macaddr='%s'",
            column,value,macaddr);

    int rv=sqlexecute(sql,&attr);
    if (rv!=KORE_RESULT_OK)
	/**/
    WEBUI_DEBUG;
    http_response_header(req, "location", "/things");
    http_response(req, 302, NULL, 0);

    /**/
    WEBUI_DEBUG;
    kore_free(html_rendered);
	attrfree(attr);

    return (KORE_RESULT_OK);
}