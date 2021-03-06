/* Copyright (c) 2017, Piotr Durlej
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <wingui_cgadget.h>
#include <wingui_metrics.h>
#include <wingui_color.h>
#include <wingui_form.h>
#include <wingui.h>

static void sizebox_redraw(struct gadget *g, int wd)
{
	win_color fg;
	win_color bg;
	int i, w;
	int tl;
	int m, s;
	
	tl = wm_get(WM_THIN_LINE);
	
	if (g->sizebox.custom_fg)
		fg = g->sizebox.fg;
	else
		fg = wc_get(WC_WIN_FG);
	
	if (g->sizebox.custom_bg)
		bg = g->sizebox.bg;
	else
		bg = wc_get(WC_WIN_BG);
	
	m = 2 * tl;
	s = 3 * tl;
	
	win_rect(wd, bg, 0, 0, g->rect.w, g->rect.h);
	if (g->form->zoomed)
		return;
	
	win_rect(wd, fg, m, m, g->rect.w - 2 * m, g->rect.h - 2 * m);
	
	w = g->rect.w;
	if (w == g->rect.h)
		for (i = 0; i < w; i++)
			win_hline(wd, bg, w - i - s / 2 - 1, i, s);
}

static void sizebox_remove(struct gadget *g)
{
	g->form->sizebox = NULL;
}

void sizebox_set_bg(struct gadget *g, win_color bg)
{
	g->sizebox.custom_bg = 1;
	g->sizebox.bg = bg;
	gadget_redraw(g);
}

void sizebox_set_fg(struct gadget *g, win_color fg)
{
	g->sizebox.custom_fg = 1;
	g->sizebox.fg = fg;
	gadget_redraw(g);
}

struct gadget *sizebox_creat(struct form *f, int w, int h)
{
	struct gadget *g;
	
	g = gadget_creat(f, f->workspace_rect.w - w, f->workspace_rect.h - h, w, h);
	if (!g)
		return NULL;
	
	g->remove = sizebox_remove;
	g->redraw = sizebox_redraw;
	gadget_redraw(g);
	
	f->sizebox = g;
	return g;
}
