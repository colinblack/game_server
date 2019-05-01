package ProtoBattleField {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoBattleField.HeroReward;
	import ProtoBattleField.ItemReward;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class UserReward extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const EXP:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.UserReward.exp", "exp", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var exp:uint;

		/**
		 *  @private
		 */
		public static const COIN:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.UserReward.coin", "coin", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var coin:uint;

		/**
		 *  @private
		 */
		public static const WOOD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.UserReward.wood", "wood", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var wood:uint;

		/**
		 *  @private
		 */
		public static const FOOD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.UserReward.food", "food", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var food:uint;

		/**
		 *  @private
		 */
		public static const IRON:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.UserReward.iron", "iron", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var iron:uint;

		/**
		 *  @private
		 */
		public static const GEM:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.UserReward.gem", "gem", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var gem:uint;

		/**
		 *  @private
		 */
		public static const HEXP:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoBattleField.UserReward.hexp", "hexp", (7 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBattleField.HeroReward; });

		[ArrayElementType("ProtoBattleField.HeroReward")]
		public var hexp:Array = [];

		/**
		 *  @private
		 */
		public static const KILL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.UserReward.kill", "kill", (8 << 3) | com.netease.protobuf.WireType.VARINT);

		private var kill$field:uint;

		private var hasField$0:uint = 0;

		public function clearKill():void {
			hasField$0 &= 0xfffffffe;
			kill$field = new uint();
		}

		public function get hasKill():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set kill(value:uint):void {
			hasField$0 |= 0x1;
			kill$field = value;
		}

		public function get kill():uint {
			return kill$field;
		}

		/**
		 *  @private
		 */
		public static const HURT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.UserReward.hurt", "hurt", (9 << 3) | com.netease.protobuf.WireType.VARINT);

		private var hurt$field:uint;

		public function clearHurt():void {
			hasField$0 &= 0xfffffffd;
			hurt$field = new uint();
		}

		public function get hasHurt():Boolean {
			return (hasField$0 & 0x2) != 0;
		}

		public function set hurt(value:uint):void {
			hasField$0 |= 0x2;
			hurt$field = value;
		}

		public function get hurt():uint {
			return hurt$field;
		}

		/**
		 *  @private
		 */
		public static const HEAD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.UserReward.head", "head", (10 << 3) | com.netease.protobuf.WireType.VARINT);

		private var head$field:uint;

		public function clearHead():void {
			hasField$0 &= 0xfffffffb;
			head$field = new uint();
		}

		public function get hasHead():Boolean {
			return (hasField$0 & 0x4) != 0;
		}

		public function set head(value:uint):void {
			hasField$0 |= 0x4;
			head$field = value;
		}

		public function get head():uint {
			return head$field;
		}

		/**
		 *  @private
		 */
		public static const REWARD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.UserReward.reward", "reward", (11 << 3) | com.netease.protobuf.WireType.VARINT);

		private var reward$field:uint;

		public function clearReward():void {
			hasField$0 &= 0xfffffff7;
			reward$field = new uint();
		}

		public function get hasReward():Boolean {
			return (hasField$0 & 0x8) != 0;
		}

		public function set reward(value:uint):void {
			hasField$0 |= 0x8;
			reward$field = value;
		}

		public function get reward():uint {
			return reward$field;
		}

		/**
		 *  @private
		 */
		public static const BKILL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.UserReward.bkill", "bkill", (12 << 3) | com.netease.protobuf.WireType.VARINT);

		private var bkill$field:uint;

		public function clearBkill():void {
			hasField$0 &= 0xffffffef;
			bkill$field = new uint();
		}

		public function get hasBkill():Boolean {
			return (hasField$0 & 0x10) != 0;
		}

		public function set bkill(value:uint):void {
			hasField$0 |= 0x10;
			bkill$field = value;
		}

		public function get bkill():uint {
			return bkill$field;
		}

		/**
		 *  @private
		 */
		public static const ITEM:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoBattleField.UserReward.item", "item", (13 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBattleField.ItemReward; });

		[ArrayElementType("ProtoBattleField.ItemReward")]
		public var item:Array = [];

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.exp);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.coin);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.wood);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.food);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.iron);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.gem);
			for (var hexp$index:uint = 0; hexp$index < this.hexp.length; ++hexp$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 7);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.hexp[hexp$index]);
			}
			if (hasKill) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 8);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, kill$field);
			}
			if (hasHurt) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 9);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, hurt$field);
			}
			if (hasHead) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 10);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, head$field);
			}
			if (hasReward) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 11);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, reward$field);
			}
			if (hasBkill) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 12);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, bkill$field);
			}
			for (var item$index:uint = 0; item$index < this.item.length; ++item$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 13);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.item[item$index]);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var exp$count:uint = 0;
			var coin$count:uint = 0;
			var wood$count:uint = 0;
			var food$count:uint = 0;
			var iron$count:uint = 0;
			var gem$count:uint = 0;
			var kill$count:uint = 0;
			var hurt$count:uint = 0;
			var head$count:uint = 0;
			var reward$count:uint = 0;
			var bkill$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (exp$count != 0) {
						throw new flash.errors.IOError('Bad data format: UserReward.exp cannot be set twice.');
					}
					++exp$count;
					this.exp = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (coin$count != 0) {
						throw new flash.errors.IOError('Bad data format: UserReward.coin cannot be set twice.');
					}
					++coin$count;
					this.coin = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (wood$count != 0) {
						throw new flash.errors.IOError('Bad data format: UserReward.wood cannot be set twice.');
					}
					++wood$count;
					this.wood = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (food$count != 0) {
						throw new flash.errors.IOError('Bad data format: UserReward.food cannot be set twice.');
					}
					++food$count;
					this.food = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (iron$count != 0) {
						throw new flash.errors.IOError('Bad data format: UserReward.iron cannot be set twice.');
					}
					++iron$count;
					this.iron = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (gem$count != 0) {
						throw new flash.errors.IOError('Bad data format: UserReward.gem cannot be set twice.');
					}
					++gem$count;
					this.gem = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					this.hexp.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoBattleField.HeroReward()));
					break;
				case 8:
					if (kill$count != 0) {
						throw new flash.errors.IOError('Bad data format: UserReward.kill cannot be set twice.');
					}
					++kill$count;
					this.kill = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 9:
					if (hurt$count != 0) {
						throw new flash.errors.IOError('Bad data format: UserReward.hurt cannot be set twice.');
					}
					++hurt$count;
					this.hurt = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 10:
					if (head$count != 0) {
						throw new flash.errors.IOError('Bad data format: UserReward.head cannot be set twice.');
					}
					++head$count;
					this.head = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 11:
					if (reward$count != 0) {
						throw new flash.errors.IOError('Bad data format: UserReward.reward cannot be set twice.');
					}
					++reward$count;
					this.reward = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 12:
					if (bkill$count != 0) {
						throw new flash.errors.IOError('Bad data format: UserReward.bkill cannot be set twice.');
					}
					++bkill$count;
					this.bkill = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 13:
					this.item.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoBattleField.ItemReward()));
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
