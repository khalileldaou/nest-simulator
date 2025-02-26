# models/CMakeLists.txt
#
# This file is part of NEST.
#
# Copyright (C) 2004 The NEST Initiative
#
# NEST is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# NEST is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with NEST.  If not, see <http://www.gnu.org/licenses/>.

set(models_sources
    ac_generator.h ac_generator.cpp
    aeif_cond_alpha.h aeif_cond_alpha.cpp
    aeif_cond_alpha_multisynapse.h aeif_cond_alpha_multisynapse.cpp
    aeif_cond_beta_multisynapse.h aeif_cond_beta_multisynapse.cpp
    aeif_cond_exp.h aeif_cond_exp.cpp
    aeif_psc_alpha.h aeif_psc_alpha.cpp
    aeif_psc_exp.h aeif_psc_exp.cpp
    aeif_psc_delta.h aeif_psc_delta.cpp
    aeif_psc_delta_clopath.h aeif_psc_delta_clopath.cpp
    amat2_psc_exp.h amat2_psc_exp.cpp
    bernoulli_synapse.h
    binary_neuron.h
    cm_default.h cm_default.cpp
    cm_tree.h cm_tree.cpp
    cm_compartmentcurrents.h cm_compartmentcurrents.cpp
    clopath_synapse.h
    cont_delay_synapse.h cont_delay_synapse_impl.h
    correlation_detector.h correlation_detector.cpp
    correlomatrix_detector.h correlomatrix_detector.cpp
    correlospinmatrix_detector.h correlospinmatrix_detector.cpp
    dc_generator.h dc_generator.cpp
    diffusion_connection.h
    erfc_neuron.h erfc_neuron.cpp
    gamma_sup_generator.h gamma_sup_generator.cpp
    gap_junction.h
    gauss_rate.h gauss_rate.cpp
    gif_psc_exp.h gif_psc_exp.cpp
    gif_psc_exp_multisynapse.h gif_psc_exp_multisynapse.cpp
    gif_cond_exp.h gif_cond_exp.cpp
    gif_cond_exp_multisynapse.h gif_cond_exp_multisynapse.cpp
    gif_pop_psc_exp.h gif_pop_psc_exp.cpp
    ginzburg_neuron.h ginzburg_neuron.cpp
    glif_cond.h glif_cond.cpp
    glif_psc.h glif_psc.cpp
    hh_cond_exp_traub.h hh_cond_exp_traub.cpp
    hh_cond_beta_gap_traub.h hh_cond_beta_gap_traub.cpp
    hh_psc_alpha.h hh_psc_alpha.cpp
    hh_psc_alpha_clopath.h hh_psc_alpha_clopath.cpp
    hh_psc_alpha_gap.h hh_psc_alpha_gap.cpp
    ht_synapse.h
    ht_neuron.h ht_neuron.cpp
    iaf_chs_2007.cpp iaf_chs_2007.h
    iaf_chxk_2008.cpp iaf_chxk_2008.h
    iaf_cond_alpha.h iaf_cond_alpha.cpp
    iaf_cond_alpha_mc.h iaf_cond_alpha_mc.cpp
    iaf_cond_beta.h iaf_cond_beta.cpp
    iaf_cond_exp.h iaf_cond_exp.cpp
    iaf_cond_exp_sfa_rr.h iaf_cond_exp_sfa_rr.cpp
    iaf_psc_alpha.h iaf_psc_alpha.cpp
    iaf_psc_alpha_multisynapse.h iaf_psc_alpha_multisynapse.cpp
    iaf_psc_alpha_ps.cpp iaf_psc_alpha_ps.h
    iaf_psc_delta.h iaf_psc_delta.cpp
    iaf_psc_delta_ps.cpp iaf_psc_delta_ps.h
    iaf_psc_exp.h iaf_psc_exp.cpp
    iaf_psc_exp_htum.h iaf_psc_exp_htum.cpp
    iaf_psc_exp_multisynapse.h iaf_psc_exp_multisynapse.cpp
    iaf_psc_exp_ps.cpp iaf_psc_exp_ps.h
    iaf_psc_exp_ps_lossless.cpp iaf_psc_exp_ps_lossless.h
    izhikevich.h izhikevich.cpp
    jonke_synapse.h
    lin_rate.h lin_rate.cpp
    mat2_psc_exp.h mat2_psc_exp.cpp
    mcculloch_pitts_neuron.h mcculloch_pitts_neuron.cpp
    mip_generator.h mip_generator.cpp
    modelsmodule.h modelsmodule.cpp
    multimeter.h multimeter.cpp
    music_cont_in_proxy.h music_cont_in_proxy.cpp
    music_cont_out_proxy.h music_cont_out_proxy.cpp
    music_event_in_proxy.h music_event_in_proxy.cpp
    music_event_out_proxy.h music_event_out_proxy.cpp
    music_rate_in_proxy.h music_rate_in_proxy.cpp
    music_rate_out_proxy.h music_rate_out_proxy.cpp
    music_message_in_proxy.h music_message_in_proxy.cpp
    noise_generator.h noise_generator.cpp
    parrot_neuron.h parrot_neuron.cpp
    parrot_neuron_ps.cpp parrot_neuron_ps.h
    inhomogeneous_poisson_generator.h inhomogeneous_poisson_generator.cpp
    poisson_generator.h poisson_generator.cpp
    poisson_generator_ps.cpp poisson_generator_ps.h
    pp_psc_delta.h pp_psc_delta.cpp
    pp_cond_exp_mc_urbanczik.h pp_cond_exp_mc_urbanczik.cpp
    ppd_sup_generator.h ppd_sup_generator.cpp
    pulsepacket_generator.h pulsepacket_generator.cpp
    quantal_stp_synapse.h quantal_stp_synapse_impl.h
    rate_connection_delayed.h
    rate_connection_instantaneous.h
    rate_neuron_opn.h rate_neuron_opn_impl.h
    rate_neuron_ipn.h rate_neuron_ipn_impl.h
    rate_transformer_node.h rate_transformer_node_impl.h
    siegert_neuron.h siegert_neuron.cpp
    sigmoid_rate.h sigmoid_rate.cpp
    sigmoid_rate_gg_1998.h sigmoid_rate_gg_1998.cpp
    sinusoidal_poisson_generator.h sinusoidal_poisson_generator.cpp
    sinusoidal_gamma_generator.h sinusoidal_gamma_generator.cpp
    spike_recorder.h spike_recorder.cpp
    spike_generator.h spike_generator.cpp
    spin_detector.h spin_detector.cpp
    spike_train_injector.h spike_train_injector.cpp
    static_synapse.h
    static_synapse_hom_w.h
    stdp_dopamine_synapse.h stdp_dopamine_synapse.cpp
    stdp_nn_pre_centered_synapse.h
    stdp_nn_restr_synapse.h
    stdp_nn_symm_synapse.h
    stdp_pl_synapse_hom.h stdp_pl_synapse_hom.cpp
    stdp_synapse.h
    stdp_synapse_facetshw_hom.h stdp_synapse_facetshw_hom_impl.h
    stdp_synapse_hom.h stdp_synapse_hom.cpp
    stdp_triplet_synapse.h
    step_current_generator.h step_current_generator.cpp
    step_rate_generator.h step_rate_generator.cpp
    tanh_rate.h tanh_rate.cpp
    threshold_lin_rate.h threshold_lin_rate.cpp
    tsodyks2_synapse.h
    tsodyks_synapse.h
    tsodyks_synapse_hom.h tsodyks_synapse_hom.cpp
    urbanczik_synapse.h
    volume_transmitter.h volume_transmitter.cpp
    vogels_sprekeler_synapse.h
    weight_recorder.h weight_recorder.cpp
    spike_dilutor.h spike_dilutor.cpp
)

add_library(models ${models_sources})
set_target_properties(models
    PROPERTIES
    VERSION ${NEST_VERSION}
    SOVERSION 3
)
target_link_libraries(models nestutil sli_lib nestkernel)

target_include_directories(models PRIVATE
    ${PROJECT_SOURCE_DIR}/thirdparty
    ${PROJECT_SOURCE_DIR}/libnestutil
    ${PROJECT_BINARY_DIR}/libnestutil
    ${PROJECT_SOURCE_DIR}/sli
    ${PROJECT_SOURCE_DIR}/nestkernel
)

install(TARGETS models
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/nest
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/nest
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

FILTER_HEADERS("${models_sources}" install_headers)
install(FILES ${install_headers}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nest)
