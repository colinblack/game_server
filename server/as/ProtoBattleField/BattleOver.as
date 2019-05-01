package ProtoBattleField {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoBattleField.UserReward;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class BattleOver extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const ATTACKERWIN:FieldDescriptor_TYPE_BOOL = new FieldDescriptor_TYPE_BOOL("ProtoBattleField.BattleOver.attackerwin", "attackerwin", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var attackerwin:Boolean;

		/**
		 *  @private
		 */
		public static const REWARD:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoBattleField.BattleOver.reward", "reward", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBattleField.UserReward; });

		private var reward$field:ProtoBattleField.UserReward;

		public function clearReward():void {
			reward$field = null;
		}

		public function get hasReward():Boolean {
			return reward$field != null;
		}

		public function set reward(value:ProtoBattleField.UserReward):void {
			reward$field = value;
		}

		public function get reward():ProtoBattleField.UserReward {
			return reward$field;
		}

		/**
		 *  @private
		 */
		public static const GATE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.BattleOver.gate", "gate", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		private var gate$field:uint;

		private var hasField$0:uint = 0;

		public function clearGate():void {
			hasField$0 &= 0xfffffffe;
			gate$field = new uint();
		}

		public function get hasGate():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set gate(value:uint):void {
			hasField$0 |= 0x1;
			gate$field = value;
		}

		public function get gate():uint {
			return gate$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_BOOL(output, this.attackerwin);
			if (hasReward) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, reward$field);
			}
			if (hasGate) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, gate$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var attackerwin$count:uint = 0;
			var reward$count:uint = 0;
			var gate$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (attackerwin$count != 0) {
						throw new flash.errors.IOError('Bad data format: BattleOver.attackerwin cannot be set twice.');
					}
					++attackerwin$count;
					this.attackerwin = com.netease.protobuf.ReadUtils.read_TYPE_BOOL(input);
					break;
				case 2:
					if (reward$count != 0) {
						throw new flash.errors.IOError('Bad data format: BattleOver.reward cannot be set twice.');
					}
					++reward$count;
					this.reward = new ProtoBattleField.UserReward();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.reward);
					break;
				case 3:
					if (gate$count != 0) {
						throw new flash.errors.IOError('Bad data format: BattleOver.gate cannot be set twice.');
					}
					++gate$count;
					this.gate = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
