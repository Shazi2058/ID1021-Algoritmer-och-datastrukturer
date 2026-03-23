if (!loop(path, k, nxt->destination_city)) {
            int result = search_dynamic(nxt->destination_city, to, path, k + 1, current_time + nxt->time, best);
            if (result != -1) {
                if (sofar_best == -1 || result < sofar_best) {
                    sofar_best = result;
                }
            }
        }