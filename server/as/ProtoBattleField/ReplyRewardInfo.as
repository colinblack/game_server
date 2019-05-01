package ProtoBattleField {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoBattleField.Mission;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class ReplyRewardInfo extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const HISTORY:RepeatedFieldDescriptor_TYPE_UINT32 = new RepeatedFieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyRewardInfo.history", "history", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		[ArrayElementType("uint")]
		public var history:Array = [];

		/**
		 *  @private
		 */
		public static const MKILL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyRewardInfo.mkill", "mkill", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var mkill:uint;

		/**
		 *  @private
		 */
		public static const KILL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyRewardInfo.kill", "kill", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var kill:uint;

		/**
		 *  @private
		 */
		public static const OCCUPY:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyRewardInfo.occupy", "occupy", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var occupy:uint;

		/**
		 *  @private
		 */
		public static const FOCCUPY:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyRewardInfo.foccupy", "foccupy", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var foccupy:uint;

		/**
		 *  @private
		 */
		public static const RUSH:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyRewardInfo.rush", "rush", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var rush:uint;

		/**
		 *  @private
		 */
		public static const REWARD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyRewardInfo.reward", "reward", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		public var reward:uint;

		/**
		 *  @private
		 */
		public static const REWARDB:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyRewardInfo.rewardb", "rewardb", (8 << 3) | com.netease.protobuf.WireType.VARINT);

		public var rewardb:uint;

		/**
		 *  @private
		 */
		public static const MISSION:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoBattleField.ReplyRewardInfo.mission", "mission", (9 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBattleField.Mission; });

		[ArrayElementType("ProtoBattleField.Mission")]
		public var mission:Array = [];

		/**
		 *  @private
		 */
		public static const MP1:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyRewardInfo.mp1", "mp1", (10 << 3) | com.netease.protobuf.WireType.VARINT);

		public var mp1:uint;

		/**
		 *  @private
		 */
		public static const MP2:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyRewardInfo.mp2", "mp2", (11 << 3) | com.netease.protobuf.WireType.VARINT);

		public var mp2:uint;

		/**
		 *  @private
		 */
		public static const MK1:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyRewardInfo.mk1", "mk1", (12 << 3) | com.netease.protobuf.WireType.VARINT);

		public var mk1:uint;

		/**
		 *  @private
		 */
		public static const MK2:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyRewardInfo.mk2", "mk2", (13 << 3) | com.netease.protobuf.WireType.VARINT);

		public var mk2:uint;

		/**
		 *  @private
		 */
		public static const MP3:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("ProtoBattleField.ReplyRewardInfo.mp3", "mp3", (14 << 3) | com.netease.protobuf.WireType.VARINT);

		public var mp3:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			for (var history$index:uint = 0; history$index < this.history.length; ++history$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.history[history$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.mkill);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.kill);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.occupy);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.foccupy);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.rush);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.reward);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 8);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.rewardb);
			for (var mission$index:uint = 0; mission$index < this.mission.length; ++mission$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 9);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.mission[mission$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 10);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.mp1);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 11);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.mp2);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 12);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.mk1);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 13);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.mk2);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 14);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.mp3);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var mkill$count:uint = 0;
			var kill$count:uint = 0;
			var occupy$count:uint = 0;
			var foccupy$count:uint = 0;
			var rush$count:uint = 0;
			var reward$count:uint = 0;
			var rewardb$count:uint = 0;
			var mp1$count:uint = 0;
			var mp2$count:uint = 0;
			var mk1$count:uint = 0;
			var mk2$count:uint = 0;
			var mp3$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if ((tag & 7) == com.netease.protobuf.WireType.LENGTH_DELIMITED) {
						com.netease.protobuf.ReadUtils.readPackedRepeated(input, com.netease.protobuf.ReadUtils.read_TYPE_UINT32, this.history);
						break;
					}
					this.history.push(com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input));
					break;
				case 2:
					if (mkill$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyRewardInfo.mkill cannot be set twice.');
					}
					++mkill$count;
					this.mkill = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (kill$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyRewardInfo.kill cannot be set twice.');
					}
					++kill$count;
					this.kill = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (occupy$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyRewardInfo.occupy cannot be set twice.');
					}
					++occupy$count;
					this.occupy = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (foccupy$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyRewardInfo.foccupy cannot be set twice.');
					}
					++foccupy$count;
					this.foccupy = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 6:
					if (rush$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyRewardInfo.rush cannot be set twice.');
					}
					++rush$count;
					this.rush = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 7:
					if (reward$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyRewardInfo.reward cannot be set twice.');
					}
					++reward$count;
					this.reward = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 8:
					if (rewardb$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyRewardInfo.rewardb cannot be set twice.');
					}
					++rewardb$count;
					this.rewardb = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 9:
					this.mission.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoBattleField.Mission()));
					break;
				case 10:
					if (mp1$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyRewardInfo.mp1 cannot be set twice.');
					}
					++mp1$count;
					this.mp1 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 11:
					if (mp2$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyRewardInfo.mp2 cannot be set twice.');
					}
					++mp2$count;
					this.mp2 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 12:
					if (mk1$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyRewardInfo.mk1 cannot be set twice.');
					}
					++mk1$count;
					this.mk1 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 13:
					if (mk2$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyRewardInfo.mk2 cannot be set twice.');
					}
					++mk2$count;
					this.mk2 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 14:
					if (mp3$count != 0) {
						throw new flash.errors.IOError('Bad data format: ReplyRewardInfo.mp3 cannot be set twice.');
					}
					++mp3$count;
					this.mp3 = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
