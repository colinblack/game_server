package ProtoYellowVip {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import DataCommon.EquipmentAllCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class FinalRewardCPP extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const EQUIPS:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoYellowVip.FinalRewardCPP.equips", "equips", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.EquipmentAllCPP; });

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
		public static const COIN:FieldDescriptor_TYPE_INT32 = new FieldDescriptor_TYPE_INT32("ProtoYellowVip.FinalRewardCPP.coin", "coin", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		private var coin$field:int;

		private var hasField$0:uint = 0;

		public function clearCoin():void {
			hasField$0 &= 0xfffffffe;
			coin$field = new int();
		}

		public function get hasCoin():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set coin(value:int):void {
			hasField$0 |= 0x1;
			coin$field = value;
		}

		public function get coin():int {
			return coin$field;
		}

		/**
		 *  @private
		 */
		public static const WOOD:FieldDescriptor_TYPE_INT32 = new FieldDescriptor_TYPE_INT32("ProtoYellowVip.FinalRewardCPP.wood", "wood", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		private var wood$field:int;

		public function clearWood():void {
			hasField$0 &= 0xfffffffd;
			wood$field = new int();
		}

		public function get hasWood():Boolean {
			return (hasField$0 & 0x2) != 0;
		}

		public function set wood(value:int):void {
			hasField$0 |= 0x2;
			wood$field = value;
		}

		public function get wood():int {
			return wood$field;
		}

		/**
		 *  @private
		 */
		public static const FOOD:FieldDescriptor_TYPE_INT32 = new FieldDescriptor_TYPE_INT32("ProtoYellowVip.FinalRewardCPP.food", "food", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		private var food$field:int;

		public function clearFood():void {
			hasField$0 &= 0xfffffffb;
			food$field = new int();
		}

		public function get hasFood():Boolean {
			return (hasField$0 & 0x4) != 0;
		}

		public function set food(value:int):void {
			hasField$0 |= 0x4;
			food$field = value;
		}

		public function get food():int {
			return food$field;
		}

		/**
		 *  @private
		 */
		public static const IRON:FieldDescriptor_TYPE_INT32 = new FieldDescriptor_TYPE_INT32("ProtoYellowVip.FinalRewardCPP.iron", "iron", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		private var iron$field:int;

		public function clearIron():void {
			hasField$0 &= 0xfffffff7;
			iron$field = new int();
		}

		public function get hasIron():Boolean {
			return (hasField$0 & 0x8) != 0;
		}

		public function set iron(value:int):void {
			hasField$0 |= 0x8;
			iron$field = value;
		}

		public function get iron():int {
			return iron$field;
		}

		/**
		 *  @private
		 */
		public static const HAMMER:FieldDescriptor_TYPE_INT32 = new FieldDescriptor_TYPE_INT32("ProtoYellowVip.FinalRewardCPP.hammer", "hammer", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		private var hammer$field:int;

		public function clearHammer():void {
			hasField$0 &= 0xffffffef;
			hammer$field = new int();
		}

		public function get hasHammer():Boolean {
			return (hasField$0 & 0x10) != 0;
		}

		public function set hammer(value:int):void {
			hasField$0 |= 0x10;
			hammer$field = value;
		}

		public function get hammer():int {
			return hammer$field;
		}

		/**
		 *  @private
		 */
		public static const ORDER:FieldDescriptor_TYPE_INT32 = new FieldDescriptor_TYPE_INT32("ProtoYellowVip.FinalRewardCPP.order", "order", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		private var order$field:int;

		public function clearOrder():void {
			hasField$0 &= 0xffffffdf;
			order$field = new int();
		}

		public function get hasOrder():Boolean {
			return (hasField$0 & 0x20) != 0;
		}

		public function set order(value:int):void {
			hasField$0 |= 0x20;
			order$field = value;
		}

		public function get order():int {
			return order$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			if (hasEquips) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, equips$field);
			}
			if (hasCoin) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_INT32(output, coin$field);
			}
			if (hasWood) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_INT32(output, wood$field);
			}
			if (hasFood) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
				com.netease.protobuf.WriteUtils.write_TYPE_INT32(output, food$field);
			}
			if (hasIron) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
				com.netease.protobuf.WriteUtils.write_TYPE_INT32(output, iron$field);
			}
			if (hasHammer) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
				com.netease.protobuf.WriteUtils.write_TYPE_INT32(output, hammer$field);
			}
			if (hasOrder) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
				com.netease.protobuf.WriteUtils.write_TYPE_INT32(output, order$field);
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
			var coin$count:uint = 0;
			var wood$count:uint = 0;
			var food$count:uint = 0;
			var iron$count:uint = 0;
			var hammer$count:uint = 0;
			var order$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (equips$count != 0) {
						throw new flash.errors.IOError('Bad data format: FinalRewardCPP.equips cannot be set twice.');
					}
					++equips$count;
					this.equips = new DataCommon.EquipmentAllCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.equips);
					break;
				case 2:
					if (coin$count != 0) {
						throw new flash.errors.IOError('Bad data format: FinalRewardCPP.coin cannot be set twice.');
					}
					++coin$count;
					this.coin = com.netease.protobuf.ReadUtils.read_TYPE_INT32(input);
					break;
				case 3:
					if (wood$count != 0) {
						throw new flash.errors.IOError('Bad data format: FinalRewardCPP.wood cannot be set twice.');
					}
					++wood$count;
					this.wood = com.netease.protobuf.ReadUtils.read_TYPE_INT32(input);
					break;
				case 4:
					if (food$count != 0) {
						throw new flash.errors.IOError('Bad data format: FinalRewardCPP.food cannot be set twice.');
					}
					++food$count;
					this.food = com.netease.protobuf.ReadUtils.read_TYPE_INT32(input);
					break;
				case 5:
					if (iron$count != 0) {
						throw new flash.errors.IOError('Bad data format: FinalRewardCPP.iron cannot be set twice.');
					}
					++iron$count;
					this.iron = com.netease.protobuf.ReadUtils.read_TYPE_INT32(input);
					break;
				case 6:
					if (hammer$count != 0) {
						throw new flash.errors.IOError('Bad data format: FinalRewardCPP.hammer cannot be set twice.');
					}
					++hammer$count;
					this.hammer = com.netease.protobuf.ReadUtils.read_TYPE_INT32(input);
					break;
				case 7:
					if (order$count != 0) {
						throw new flash.errors.IOError('Bad data format: FinalRewardCPP.order cannot be set twice.');
					}
					++order$count;
					this.order = com.netease.protobuf.ReadUtils.read_TYPE_INT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
