package ProtoBattleField {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import DataCommon.EquipmentAllCPP;
	import DataCommon.CommonBaseRewardCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class ReplyKillReward extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const EQUIPS:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoBattleField.ReplyKillReward.equips", "equips", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.EquipmentAllCPP; });

		private var equips$field:DataCommon.EquipmentAllCPP;

		public function clearEquips():void {
			equips$field = null;
		}

		public function get hasEquips():Boolean {
			return equips$field != null;
		}

		public function set equips(value:DataCommon.EquipmentAllCPP):void {
			equips$field = value;
		}

		public function get equips():DataCommon.EquipmentAllCPP {
			return equips$field;
		}

		/**
		 *  @private
		 */
		public static const BASE:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoBattleField.ReplyKillReward.base", "base", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.CommonBaseRewardCPP; });

		private var base$field:DataCommon.CommonBaseRewardCPP;

		public function clearBase():void {
			base$field = null;
		}

		public function get hasBase():Boolean {
			return base$field != null;
		}

		public function set base(value:DataCommon.CommonBaseRewardCPP):void {
			base$field = value;
		}

		public function get base():DataCommon.CommonBaseRewardCPP {
			return base$field;
		}

		/**
		 *  @private
		 */
		public static const EXPLOIT_BOX_CNT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyKillReward.exploit_box_cnt", "exploitBoxCnt", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var exploitBoxCnt:uint;

		/**
		 *  @private
		 */
		public static const MULTIPLE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyKillReward.multiple", "multiple", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var multiple:uint;

		/**
		 *  @private
		 */
		public static const EQUIPS_CNT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyKillReward.equips_cnt", "equipsCnt", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		private var equips_cnt$field:uint;

		private var hasField$0:uint = 0;

		public function clearEquipsCnt():void {
			hasField$0 &= 0xfffffffe;
			equips_cnt$field = new uint();
		}

		public function get hasEquipsCnt():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set equipsCnt(value:uint):void {
			hasField$0 |= 0x1;
			equips_cnt$field = value;
		}

		public function get equipsCnt():uint {
			return equips_cnt$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			if (hasEquips) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, equips$field);
			}
			if (hasBase) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, base$field);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.exploitBoxCnt);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.multiple);
			if (hasEquipsCnt) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, equips_cnt$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var equips$count:uint = 0;
			var base$count:uint = 0;
			var exploit_box_cnt$count:uint = 0;
			var multiple$count:uint = 0;
			var equips_cnt$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (equips$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyKillReward.equips cannot be set twice.');
					}
					++equips$count;
					this.equips = new DataCommon.EquipmentAllCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.equips);
					break;
				case 2:
					if (base$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyKillReward.base cannot be set twice.');
					}
					++base$count;
					this.base = new DataCommon.CommonBaseRewardCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.base);
					break;
				case 3:
					if (exploit_box_cnt$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyKillReward.exploitBoxCnt cannot be set twice.');
					}
					++exploit_box_cnt$count;
					this.exploitBoxCnt = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (multiple$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyKillReward.multiple cannot be set twice.');
					}
					++multiple$count;
					this.multiple = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (equips_cnt$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyKillReward.equipsCnt cannot be set twice.');
					}
					++equips_cnt$count;
					this.equipsCnt = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
