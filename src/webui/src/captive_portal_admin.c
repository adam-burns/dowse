
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

int captive_portal_admin(struct http_request * req) {
    log_entering();
    template_t tmpl;
    attributes_set_t attr;
    u_int8_t *html_rendered;
    struct kore_buf *out;
    size_t len;
    out = kore_buf_alloc(0);
	attr=attrinit();

	/**/

    sql_select_into_attributes(
            "SELECT count(id) as how_much, min(age) as first_age,max(age) as last_age,E.* "
            "FROM event E WHERE recognized=0 "
            "GROUP BY macaddr,description ",
            "captive_portal_event",
            &attr);

    /* Put the captive portal redirect */
    sqlexecute("CALL redirect_admin_to_captive_portal('admin');",&attr);

    template_load(asset_captive_portal_admin_html,asset_len_captive_portal_admin_html,&tmpl);
    template_apply(&tmpl,attr,out);

	/**/
    html_rendered = kore_buf_release(out, &len);
    http_response(req, 200, html_rendered, len);

    /**/
    kore_free(html_rendered);
	attrfree(attr);

    return (KORE_RESULT_OK);
}
