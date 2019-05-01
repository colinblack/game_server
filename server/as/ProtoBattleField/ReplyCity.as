package ProtoBattleField {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoBattleField.Turn;
	import ProtoBattleField.HeroUid;
	import ProtoBattleField.UserInfo;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class ReplyCity extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const ATTACKER:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoBattleField.ReplyCity.attacker", "attacker", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBattleField.HeroUid; });

		[ArrayElementType("ProtoBattleField.HeroUid")]
		public var attacker:Array = [];

		/**
		 *  @private
		 */
		public static const DEFENDER:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoBattleField.ReplyCity.defender", "defender", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBattleField.HeroUid; });

		[ArrayElementType("ProtoBattleField.HeroUid")]
		public var defender:Array = [];

		/**
		 *  @private
		 */
		public static const INFO:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoBattleField.ReplyCity.info", "info", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBattleField.UserInfo; });

		[ArrayElementType("ProtoBattleField.UserInfo")]
		public var info:Array = [];

		/**
		 *  @private
		 */
		public static const TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyCity.ts", "ts", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		private var ts$field:uint;

		private var hasField$0:uint = 0;

		public function clearTs():void {
			hasField$0 &= 0xfffffffe;
			ts$field = new uint();
		}

		public function get hasTs():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set ts(value:uint):void {
			hasField$0 |= 0x1;
			ts$field = value;
		}

		public function get ts():uint {
			return ts$field;
		}

		/**
		 *  @private
		 */
		public static const NEXTTS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyCity.nextts", "nextts", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		private var nextts$field:uint;

		public function clearNextts():void {
			hasField$0 &= 0xfffffffd;
			nextts$field = new uint();
		}

		public function get hasNextts():Boolean {
			return (hasField$0 & 0x2) != 0;
		}

		public function set nextts(value:uint):void {
			hasField$0 |= 0x2;
			nextts$field = value;
		}

		public function get nextts():uint {
			return nextts$field;
		}

		/**
		 *  @private
		 */
		public static const TURN:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoBattleField.ReplyCity.turn", "turn", (6 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBattleField.Turn; });

		private var turn$field:ProtoBattleField.Turn;

		public function clearTurn():void {
			turn$field = null;
		}

		public function get hasTurn():Boolean {
			return turn$field != null;
		}

		public function set turn(value:ProtoBattleField.Turn):void {
			turn$field = value;
		}

		public function get turn():ProtoBattleField.Turn {
			return turn$field;
		}

		/**
		 *  @private
		 */
		public static const GID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyCity.gid", "gid", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		public var gid:uint;

		/**
		 *  @private
		 */
		public static const TYPE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyCity.type", "type", (8 << 3) | com.netease.protobuf.WireType.VARINT);

		public var type:uint;

		/**
		 *  @private
		 */
		public static const CID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyCity.cid", "cid", (9 << 3) | com.netease.protobuf.WireType.VARINT);

		public var cid:uint;

		/**
		 *  @private
		 */
		public static const UID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyCity.uid", "uid", (10 << 3) | com.netease.protobuf.WireType.VARINT);

		public var uid:uint;

		/**
		 *  @private
		 */
		public static const GATE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyCity.gate", "gate", (11 << 3) | com.netease.protobuf.WireType.VARINT);

		public var gate:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			for (var attacker$index:uint = 0; attacker$index < this.attacker.length; ++attacker$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.attacker[attacker$index]);
			}
			for (var defender$index:uint = 0; defender$index < this.defender.length; ++defender$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.defender[defender$index]);
			}
			for (var info$index:uint = 0; info$index < this.info.length; ++info$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.info[info$index]);
			}
			if (hasTs) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, ts$field);
			}
			if (hasNextts) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, nextts$field);
			}
			if (hasTurn) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 6);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, turn$field);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.gid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 8);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.type);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 9);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.cid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 10);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.uid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 11);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.gate);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var ts$count:uint = 0;
			var nextts$count:uint = 0;
			var turn$count:uint = 0;
			var gid$count:uint = 0;
			var type$count:uint = 0;
			var cid$count:uint = 0;
			var uid$count:uint = 0;
			var gate$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					this.attacker.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoBattleField.HeroUid()));
					break;
				case 2:
					this.defender.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoBattleField.HeroUid()));
					break;
				case 3:
					this.info.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoBattleField.UserInfo()));
					break;
				case 4:
					if (ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyCity.ts cannot be set twice.');
					}
					++ts$count;
					this.ts = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (nextts$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyCity.nextts cannot be set twice.');
					}
					++nextts$count;
					this.nextts = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (turn$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyCity.turn cannot be set twice.');
					}
					++turn$count;
					this.turn = new ProtoBattleField.Turn();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.turn);
					break;
				case 7:
					if (gid$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyCity.gid cannot be set twice.');
					}
					++gid$count;
					this.gid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 8:
					if (type$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyCity.type cannot be set twice.');
					}
					++type$count;
					this.type = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 9:
					if (cid$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyCity.cid cannot be set twice.');
					}
					++cid$count;
					this.cid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 10:
					if (uid$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyCity.uid cannot be set twice.');
					}
					++uid$count;
					this.uid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 11:
					if (gate$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyCity.gate cannot be set twice.');
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
