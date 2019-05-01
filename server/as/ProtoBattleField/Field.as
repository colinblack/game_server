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
	import ProtoBattleField.Hero;
	import ProtoBattleField.City;
	import ProtoBattleField.RMIField;
	import ProtoBattleField.BattleReward;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class Field extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const HERO:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoBattleField.Field.hero", "hero", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBattleField.Hero; });

		[ArrayElementType("ProtoBattleField.Hero")]
		public var hero:Array = [];

		/**
		 *  @private
		 */
		public static const CITY:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoBattleField.Field.city", "city", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBattleField.City; });

		[ArrayElementType("ProtoBattleField.City")]
		public var city:Array = [];

		/**
		 *  @private
		 */
		public static const MISSION:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoBattleField.Field.mission", "mission", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBattleField.Mission; });

		[ArrayElementType("ProtoBattleField.Mission")]
		public var mission:Array = [];

		/**
		 *  @private
		 */
		public static const RMI:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoBattleField.Field.rmi", "rmi", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBattleField.RMIField; });

		public var rmi:ProtoBattleField.RMIField;

		/**
		 *  @private
		 */
		public static const REWARD:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoBattleField.Field.reward", "reward", (5 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBattleField.BattleReward; });

		public var reward:ProtoBattleField.BattleReward;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			for (var hero$index:uint = 0; hero$index < this.hero.length; ++hero$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.hero[hero$index]);
			}
			for (var city$index:uint = 0; city$index < this.city.length; ++city$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.city[city$index]);
			}
			for (var mission$index:uint = 0; mission$index < this.mission.length; ++mission$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.mission[mission$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.rmi);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.reward);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var rmi$count:uint = 0;
			var reward$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					this.hero.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoBattleField.Hero()));
					break;
				case 2:
					this.city.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoBattleField.City()));
					break;
				case 3:
					this.mission.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoBattleField.Mission()));
					break;
				case 4:
					if (rmi$count != 0) {
						throw new flash.errors.IOError('Bad data format: Field.rmi cannot be set twice.');
					}
					++rmi$count;
					this.rmi = new ProtoBattleField.RMIField();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.rmi);
					break;
				case 5:
					if (reward$count != 0) {
						throw new flash.errors.IOError('Bad data format: Field.reward cannot be set twice.');
					}
					++reward$count;
					this.reward = new ProtoBattleField.BattleReward();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.reward);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
