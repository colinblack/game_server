package User {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoScience.ScienceItemCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class Science extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const ITEMS:RepeatedFieldDescriptor_TYPE_MESSAGE = new RepeatedFieldDescriptor_TYPE_MESSAGE("User.Science.items", "items", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoScience.ScienceItemCPP; });

		[ArrayElementType("ProtoScience.ScienceItemCPP")]
		public var items:Array = [];

		/**
		 *  @private
		 */
		public static const RECRUIT_HERO_CAPACITY:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Science.recruit_hero_capacity", "recruitHeroCapacity", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var recruitHeroCapacity:uint;

		/**
		 *  @private
		 */
		public static const SOLDIERS_ROW:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Science.soldiers_row", "soldiersRow", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var soldiersRow:uint;

		/**
		 *  @private
		 */
		public static const SOLDIERS_LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Science.soldiers_level", "soldiersLevel", (4 << 3) | com.netease.protobuf.WireType.VARINT);

		public var soldiersLevel:uint;

		/**
		 *  @private
		 */
		public static const EXPLOIT_BOX_LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.Science.exploit_box_level", "exploitBoxLevel", (5 << 3) | com.netease.protobuf.WireType.VARINT);

		public var exploitBoxLevel:uint;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			for (var items$index:uint = 0; items$index < this.items.length; ++items$index) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.items[items$index]);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.recruitHeroCapacity);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.soldiersRow);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.soldiersLevel);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 5);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.exploitBoxLevel);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var recruit_hero_capacity$count:uint = 0;
			var soldiers_row$count:uint = 0;
			var soldiers_level$count:uint = 0;
			var exploit_box_level$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					this.items.push(com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, new ProtoScience.ScienceItemCPP()));
					break;
				case 2:
					if (recruit_hero_capacity$count != 0) {
						throw new flash.errors.IOError('Bad data format: Science.recruitHeroCapacity cannot be set twice.');
					}
					++recruit_hero_capacity$count;
					this.recruitHeroCapacity = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (soldiers_row$count != 0) {
						throw new flash.errors.IOError('Bad data format: Science.soldiersRow cannot be set twice.');
					}
					++soldiers_row$count;
					this.soldiersRow = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (soldiers_level$count != 0) {
						throw new flash.errors.IOError('Bad data format: Science.soldiersLevel cannot be set twice.');
					}
					++soldiers_level$count;
					this.soldiersLevel = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 5:
					if (exploit_box_level$count != 0) {
						throw new flash.errors.IOError('Bad data format: Science.exploitBoxLevel cannot be set twice.');
					}
					++exploit_box_level$count;
					this.exploitBoxLevel = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
