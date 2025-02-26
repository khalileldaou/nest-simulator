/*
 *  stdp_synapse_facetshw_hom.h
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef STDP_SYNAPSE_FACETSHW_HOM_H
#define STDP_SYNAPSE_FACETSHW_HOM_H

// C++ includes:
#include <cmath>

// Includes from nestkernel:
#include "common_synapse_properties.h"
#include "connection.h"

namespace nest
{

/* BeginUserDocs: synapse, spike-timing-dependent plasticity

Short description
+++++++++++++++++

Synapse type for spike-timing dependent plasticity using homogeneous parameters

Description
+++++++++++

``stdp_facetshw_synapse`` is a connector to create synapses with spike-timing
dependent plasticity (as defined in [1]_).
This connector is a modified version of ``stdp_synapse``.
It includes constraints of the hardware developed in the FACETS (BrainScaleS)
project [2]_, [3]_, as for example, 4-bit weight resolution, sequential updates of groups
of synapses and reduced symmetric nearest-neighbor spike pairing scheme. For
details see [3]_.
The modified spike pairing scheme requires the calculation of ``tau_minus_``
within this synapse and not at the neuron site via ``Kplus_`` like in
``stdp_synapse_hom``.

.. warning::

   This synaptic plasticity rule does not take
   :ref:`precise spike timing <sim_precise_spike_times>` into
   account. When calculating the weight update, the precise spike time part
   of the timestamp is ignored.

The synapse IDs are assigned to each synapse in an ascending order (0,1,2,
...) according their first presynaptic activity and is used to group synapses
that are updated at once. It is possible to avoid activity dependent synapse
ID assignments by manually setting the no_synapses and the synapse_id(s)
before running the simulation. The weights will be discretized after the
first presynaptic activity at a synapse.

Parameters
++++++++++

======================= =========== ===========================================
**Common properties**
-------------------------------------------------------------------------------
 tau_plus               ms          Time constant of STDP window, causal branch
 tau_minus_stdp         ms          Time constant of STDP window, anti-causal
                                    branch
 Wmax                   real        Maximum allowed weight
 no_synapses            integer     Total number of synapses
 synapses_per_driver    integer     Number of synapses updated at once
 driver_readout_time    real        Time for processing of one synapse row
                                    (synapse line driver)
 readout_cycle_duration real        Duration between two subsequent
                                    updates of same synapse (synapse line
                                    driver)
 lookuptable_0          list of     Three look-up tables (LUT)
                        integers
 lookuptable_1          list of
                        integers
 lookuptable_2          list of
                        integers
 configbit_0            list of     Configuration bits for evaluation
                        integers    function. For details see code in
                                    function ``eval_function_`` and [4]_
                                    (configbit[0]=e_cc, ..[1]_=e_ca,
                                    ..[2]_=e_ac, ..[3]=e_aa).
                                    Depending on these two sets of
                                    configuration bits weights are updated
                                    according LUTs (out of three: (1,0),
                                    (0,1), (1,1)). For (0,0) continue
                                    without reset.
 configbit_1            list of
                        integers
 reset_pattern          list of     Configuration bits for reset behavior.
                        integers    Two bits for each LUT (reset causal
                                    and acausal). In hardware only (all
                                    false; never reset) or (all true;
                                    always reset) is allowed.
======================= =========== ===========================================

Common properties can only be set on the synapse model using
:py:func:`.SetDefaults`.

============  ======= =====================================================
**Individual properties**
---------------------------------------------------------------------------
 a_causal     real    Causal and anti-causal spike pair accumulations
 a_acausal    real
 a_thresh_th  real    Two thresholds used in evaluation function
                      No common property, because variation of analog
                      synapse circuitry can be applied here
 a_thresh_tl  real
 synapse_id   integer Synapse ID, used to assign synapses to groups (synapse
                      drivers)
============  ======= =====================================================

Transmits
+++++++++

SpikeEvent

References
++++++++++

.. [1] Morrison A, Diesmann M, Gerstner W (2008). Phenomenological models of
       synaptic plasticity based on spike-timing. Biological Cybernetics,
       98:459-478. DOI: https://doi.org/10.1007/s00422-008-0233-1
.. [2] Schemmel J, Gruebl A, Meier K, Mueller E (2006). Implementing synaptic
       plasticity in a VLSI spiking neural network model. In Proceedings of the
       2006 International Joint Conference on Neural Networks, pp.1--6,
       IEEE Press. DOI: https://doi.org/10.1109/IJCNN.2006.246651
.. [3] Pfeil T, Potjans TC, Schrader S, Potjans W, Schemmel J, Diesmann M,
       Meier K (2012). Is a 4-bit synaptic weight resolution enough? -
       constraints on enabling spike-timing dependent plasticity in
       neuromorphic hardware. Frontiers in Neuroscience 6(90).
       DOI: https://doi.org/10.3389/fnins.2012.00090
.. [4] Friedmann, S. in preparation

See also
++++++++

stdp_synapse, tsodyks_synapse, static_synapse

EndUserDocs */

// template class forward declaration required by common properties friend
// definition

template < typename targetidentifierT >
class stdp_facetshw_synapse_hom;

/**
 * Class containing the common properties for all synapses of type
 * stdp_facetshw_synapse_hom.
 */
template < typename targetidentifierT >
class STDPFACETSHWHomCommonProperties : public CommonSynapseProperties
{
  friend class stdp_facetshw_synapse_hom< targetidentifierT >;

public:
  /**
   * Default constructor.
   * Sets all property values to defaults.
   */
  STDPFACETSHWHomCommonProperties();

  /**
   * Get all properties and put them into a dictionary.
   */
  void get_status( DictionaryDatum& d ) const;

  /**
   * Set properties from the values given in dictionary.
   */
  void set_status( const DictionaryDatum& d, ConnectorModel& cm );

  // overloaded for all supported event types
  void
  check_event( SpikeEvent& )
  {
  }

private:
  /**
   * Calculate the readout cycle duration
   */
  void calc_readout_cycle_duration_();


  // data members common to all connections
  double tau_plus_;
  double tau_minus_;
  double Wmax_;
  double weight_per_lut_entry_;

  // STDP controller parameters
  long no_synapses_;
  long synapses_per_driver_;
  double driver_readout_time_;
  double readout_cycle_duration_;
  // TODO: TP: size in memory could be reduced
  std::vector< long > lookuptable_0_;
  std::vector< long > lookuptable_1_;
  std::vector< long > lookuptable_2_; // TODO: TP: to save memory one could
                                      // introduce vector<bool> &
                                      // BoolVectorDatum
  std::vector< long > configbit_0_;
  std::vector< long > configbit_1_;
  std::vector< long > reset_pattern_;
};


/**
 * Class representing an STDP connection with homogeneous parameters, i.e.
 * parameters are the same for all synapses.
 */
template < typename targetidentifierT >
class stdp_facetshw_synapse_hom : public Connection< targetidentifierT >
{

public:
  typedef STDPFACETSHWHomCommonProperties< targetidentifierT > CommonPropertiesType;
  typedef Connection< targetidentifierT > ConnectionBase;

  static constexpr ConnectionModelProperties properties = ConnectionModelProperties::HAS_DELAY
    | ConnectionModelProperties::IS_PRIMARY | ConnectionModelProperties::SUPPORTS_HPC
    | ConnectionModelProperties::SUPPORTS_LBL;

  /**
   * Default Constructor.
   * Sets default values for all parameters. Needed by GenericConnectorModel.
   */
  stdp_facetshw_synapse_hom();

  /**
   * Copy constructor from a property object.
   * Needs to be defined properly in order for GenericConnector to work.
   */
  stdp_facetshw_synapse_hom( const stdp_facetshw_synapse_hom& ) = default;
  stdp_facetshw_synapse_hom& operator=( const stdp_facetshw_synapse_hom& ) = default;

  // Explicitly declare all methods inherited from the dependent base
  // ConnectionBase. This avoids explicit name prefixes in all places these
  // functions are used. Since ConnectionBase depends on the template parameter,
  // they are not automatically found in the base class.
  using ConnectionBase::get_delay;
  using ConnectionBase::get_delay_steps;
  using ConnectionBase::get_rport;
  using ConnectionBase::get_target;

  /**
   * Get all properties of this connection and put them into a dictionary.
   */
  void get_status( DictionaryDatum& d ) const;

  /**
   * Set properties of this connection from the values given in dictionary.
   */
  void set_status( const DictionaryDatum& d, ConnectorModel& cm );

  /**
   * Send an event to the receiver of this connection.
   * \param e The event to send
   */
  void send( Event& e, thread t, const STDPFACETSHWHomCommonProperties< targetidentifierT >& );


  class ConnTestDummyNode : public ConnTestDummyNodeBase
  {
  public:
    // Ensure proper overriding of overloaded virtual functions.
    // Return values from functions are ignored.
    using ConnTestDummyNodeBase::handles_test_event;
    port
    handles_test_event( SpikeEvent&, rport ) override
    {
      return invalid_port;
    }
  };


  /*
   * This function calls check_connection on the sender and checks if the
   * receiver accepts the event type and receptor type requested by the sender.
   * Node::check_connection() will either confirm the receiver port by returning
   * true or false if the connection should be ignored.
   * We have to override the base class' implementation, since for STDP
   * connections we have to call register_stdp_connection on the target neuron
   * to inform the Archiver to collect spikes for this connection.
   *
   * \param s The source node
   * \param r The target node
   * \param receptor_type The ID of the requested receptor type
   */
  void
  check_connection( Node& s, Node& t, rport receptor_type, const CommonPropertiesType& )
  {
    ConnTestDummyNode dummy_target;

    ConnectionBase::check_connection_( dummy_target, s, t, receptor_type );

    t.register_stdp_connection( t_lastspike_ - get_delay(), get_delay() );
  }

  void
  set_weight( double w )
  {
    weight_ = w;
  }

private:
  bool eval_function_( double a_causal,
    double a_acausal,
    double a_thresh_th,
    double a_thresh_tl,
    std::vector< long > configbit );

  // transformation biological weight <-> discrete weight (represented in index
  // of look-up table)
  unsigned int weight_to_entry_( double weight, double weight_per_lut_entry );
  double entry_to_weight_( unsigned int discrete_weight, double weight_per_lut_entry );

  unsigned int lookup_( unsigned int discrete_weight_, std::vector< long > table );

  // data members of each connection
  double weight_;
  double a_causal_;
  double a_acausal_;
  double a_thresh_th_;
  double a_thresh_tl_;

  bool init_flag_;
  long synapse_id_;
  double next_readout_time_;
  unsigned int discrete_weight_; // TODO: TP: only needed in send, move to common
                                 // properties or "static"?
  double t_lastspike_;
};

template < typename targetidentifierT >
constexpr ConnectionModelProperties stdp_facetshw_synapse_hom< targetidentifierT >::properties;

template < typename targetidentifierT >
inline bool
stdp_facetshw_synapse_hom< targetidentifierT >::eval_function_( double a_causal,
  double a_acausal,
  double a_thresh_th,
  double a_thresh_tl,
  std::vector< long > configbit )
{
  // compare charge on capacitors with thresholds and return evaluation bit
  return ( a_thresh_tl + configbit[ 2 ] * a_causal + configbit[ 1 ] * a_acausal )
    / ( 1 + configbit[ 2 ] + configbit[ 1 ] )
    > ( a_thresh_th + configbit[ 0 ] * a_causal + configbit[ 3 ] * a_acausal )
    / ( 1 + configbit[ 0 ] + configbit[ 3 ] );
}

template < typename targetidentifierT >
inline unsigned int
stdp_facetshw_synapse_hom< targetidentifierT >::weight_to_entry_( double weight, double weight_per_lut_entry )
{
  // returns the discrete weight in terms of the look-up table index
  return round( weight / weight_per_lut_entry );
}

template < typename targetidentifierT >
inline double
stdp_facetshw_synapse_hom< targetidentifierT >::entry_to_weight_( unsigned int discrete_weight,
  double weight_per_lut_entry )
{
  // returns the continuous weight
  return discrete_weight * weight_per_lut_entry;
}

template < typename targetidentifierT >
inline unsigned int
stdp_facetshw_synapse_hom< targetidentifierT >::lookup_( unsigned int discrete_weight_, std::vector< long > table )
{
  // look-up in table
  return table[ discrete_weight_ ];
}


/**
 * Send an event to the receiver of this connection.
 * \param e The event to send
 * \param p The port under which this connection is stored in the Connector.
 */
template < typename targetidentifierT >
inline void
stdp_facetshw_synapse_hom< targetidentifierT >::send( Event& e,
  thread t,
  const STDPFACETSHWHomCommonProperties< targetidentifierT >& cp )
{
  // synapse STDP dynamics

  double t_spike = e.get_stamp().get_ms();

  // remove const-ness of common properties
  // this is not a nice solution, but only a workaround
  // anyway the current implementation will presumably
  // generate wring results on distributed systems,
  // because the number of synapses counted is only
  // the number of synapses local to the current machine
  STDPFACETSHWHomCommonProperties< targetidentifierT >& cp_nonconst =
    const_cast< STDPFACETSHWHomCommonProperties< targetidentifierT >& >( cp );

  // init the readout time
  if ( not init_flag_ )
  {
    synapse_id_ = cp.no_synapses_;
    ++cp_nonconst.no_synapses_;
    cp_nonconst.calc_readout_cycle_duration_();
    next_readout_time_ = int( synapse_id_ / cp_nonconst.synapses_per_driver_ ) * cp_nonconst.driver_readout_time_;
    std::cout << "init synapse " << synapse_id_ << " - first readout time: " << next_readout_time_ << std::endl;
    init_flag_ = true;
  }

  // STDP controller is processing this synapse (synapse driver)?
  if ( t_spike > next_readout_time_ )
  {
    // transform weight to discrete representation
    discrete_weight_ = weight_to_entry_( weight_, cp_nonconst.weight_per_lut_entry_ );

    // obtain evaluation bits
    bool eval_0 = eval_function_( a_causal_, a_acausal_, a_thresh_th_, a_thresh_tl_, cp.configbit_0_ );
    bool eval_1 = eval_function_( a_causal_, a_acausal_, a_thresh_th_, a_thresh_tl_, cp.configbit_1_ );

    // select LUT, update weight and reset capacitors
    if ( eval_0 == true and eval_1 == false )
    {
      discrete_weight_ = lookup_( discrete_weight_, cp.lookuptable_0_ );
      if ( cp.reset_pattern_[ 0 ] )
      {
        a_causal_ = 0;
      }
      if ( cp.reset_pattern_[ 1 ] )
      {
        a_acausal_ = 0;
      }
    }
    else if ( eval_0 == false and eval_1 == true )
    {
      discrete_weight_ = lookup_( discrete_weight_, cp.lookuptable_1_ );
      if ( cp.reset_pattern_[ 2 ] )
      {
        a_causal_ = 0;
      }
      if ( cp.reset_pattern_[ 3 ] )
      {
        a_acausal_ = 0;
      }
    }
    else if ( eval_0 == true and eval_1 == true )
    {
      discrete_weight_ = lookup_( discrete_weight_, cp.lookuptable_2_ );
      if ( cp.reset_pattern_[ 4 ] )
      {
        a_causal_ = 0;
      }
      if ( cp.reset_pattern_[ 5 ] )
      {
        a_acausal_ = 0;
      }
    }
    // do nothing, if eval_0 == false and eval_1 == false

    while ( t_spike > next_readout_time_ )
    {
      next_readout_time_ += cp_nonconst.readout_cycle_duration_;
    }
    // std::cout << "synapse " << synapse_id_ << " updated at " << t_spike << ",
    // next readout time:
    // " << next_readout_time_ << std::endl;

    // back-transformation to continuous weight space
    weight_ = entry_to_weight_( discrete_weight_, cp.weight_per_lut_entry_ );
  }

  // t_lastspike_ = 0 initially

  double dendritic_delay = Time( Time::step( get_delay_steps() ) ).get_ms();

  // get spike history in relevant range (t1, t2] from postsynaptic neuron
  std::deque< histentry >::iterator start;
  std::deque< histentry >::iterator finish;
  get_target( t )->get_history( t_lastspike_ - dendritic_delay, t_spike - dendritic_delay, &start, &finish );

  // facilitation due to the first postsynaptic spike since the last
  // pre-synaptic spike
  if ( start != finish )
  {
    double minus_dt_causal = t_lastspike_ - ( start->t_ + dendritic_delay );

    // get_history() should make sure that
    // start->t_ > t_lastspike_ - dendritic_delay, i.e. minus_dt < 0
    assert( minus_dt_causal < -1.0 * kernel().connection_manager.get_stdp_eps() );

    a_causal_ += std::exp( minus_dt_causal / cp.tau_plus_ );

    // take only last postspike before current spike
    double minus_dt_acausal;

    --finish;
    minus_dt_acausal = ( finish->t_ + dendritic_delay ) - t_spike;

    a_acausal_ += std::exp( minus_dt_acausal / cp.tau_minus_ );
  }

  e.set_receiver( *get_target( t ) );
  e.set_weight( weight_ );
  e.set_delay_steps( get_delay_steps() );
  e.set_rport( get_rport() );
  e();

  t_lastspike_ = t_spike;
}
} // of namespace nest

#endif // of #ifndef STDP_SYNAPSE_FACETSHW_HOM_H
