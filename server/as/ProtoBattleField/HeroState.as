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
	import ProtoBattleField.Hero;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class HeroState extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const HERO:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("ProtoBattleField.HeroState.hero", "hero", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBattleField.Hero; });

		[ArrayElementType("ProtoBattleField.Hero")]
		public var hero:Array = [];

		/**
		 *  @private
		 */
		public static const REWARD:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoBattleField.HeroState.reward", "reward", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoBattleField.UserReward; });

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
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			for (var hero$index:uint = 0; hero$index < this.hero.length; ++hero$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.hero[hero$index]);
			}
			if (hasReward) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, reward$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var reward$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					this.hero.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoBattleField.Hero()));
					break;
				case 2:
					if (reward$count != 0) {
						throw new flash.errors.IOError('Bad data format: HeroState.reward cannot be set twice.');
					}
					++reward$count;
					this.reward = new ProtoBattleField.UserReward();
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
