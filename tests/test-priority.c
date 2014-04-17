/*
 * This file is part of the Nice GLib ICE library.
 *
 * (C) 2006, 2007 Collabora Ltd.
 *  Contact: Dafydd Harries
 * (C) 2006, 2007 Nokia Corporation. All rights reserved.
 *  Contact: Kai Vehmanen
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is the Nice GLib ICE library.
 *
 * The Initial Developers of the Original Code are Collabora Ltd and Nokia
 * Corporation. All Rights Reserved.
 *
 * Contributors:
 *   Dafydd Harries, Collabora Ltd.
 *
 * Alternatively, the contents of this file may be used under the terms of the
 * the GNU Lesser General Public License Version 2.1 (the "LGPL"), in which
 * case the provisions of LGPL are applicable instead of those above. If you
 * wish to allow use of your version of this file only under the terms of the
 * LGPL and not to allow others to use your version of this file under the
 * MPL, indicate your decision by deleting the provisions above and replace
 * them with the notice and other provisions required by the LGPL. If you do
 * not delete the provisions above, a recipient may use your version of this
 * file under either the MPL or the LGPL.
 */
#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "agent.h"

int
main (void)
{
  NiceCandidate *candidate;

  /* test 1 */
  candidate = nice_candidate_new (NICE_CANDIDATE_TYPE_HOST);
  g_assert (nice_candidate_jingle_priority (candidate) == 1000);
  /* Host UDP */
  candidate->transport = NICE_CANDIDATE_TRANSPORT_UDP;
  candidate->component_id = 1;
  g_assert (nice_candidate_ice_priority (candidate, FALSE, FALSE) == 0x780001FF);
  /* Host UDP reliable */
  g_assert (nice_candidate_ice_priority (candidate, TRUE, FALSE) == 0x3C0001FF);
  /* Host tcp-active unreliable */
  candidate->transport = NICE_CANDIDATE_TRANSPORT_TCP_ACTIVE;
  g_assert (nice_candidate_ice_priority (candidate, FALSE, FALSE) == 0x3CC001FF);
  /* Host tcp-active reliable */
  candidate->transport = NICE_CANDIDATE_TRANSPORT_TCP_ACTIVE;
  /* Host tcp-active reliable */
  g_assert (nice_candidate_ice_priority (candidate, TRUE, FALSE) == 0x78C001FF);
  /* srv-reflexive tcp-active reliable */
  candidate->type = NICE_CANDIDATE_TYPE_SERVER_REFLEXIVE;
  candidate->transport = NICE_CANDIDATE_TRANSPORT_TCP_ACTIVE;
  g_assert (nice_candidate_ice_priority (candidate, TRUE, FALSE) == 0x648001FF);
  /* nat-assisted srv-reflexive tcp-active reliable */
  g_assert (nice_candidate_ice_priority (candidate, TRUE, TRUE) == 0x698001FF);
  nice_candidate_free (candidate);

  /* test 2 */
  /* 2^32*MIN(O,A) + 2*MAX(O,A) + (O>A?1:0)
     = 2^32*1 + 2*5000 + 0
     = 4294977296 */
  g_assert (nice_candidate_pair_priority (1,5000) == 4294977296LL);

  /* 2^32*1 + 2*5000 + 1 = 4294977297 */
  g_assert (nice_candidate_pair_priority (5000, 1) == 4294977297LL);

  return 0;
}

