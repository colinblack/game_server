package ProtoHero {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoHero.EquipmentWrapCPP;
	import ProtoHero.HeroBaseInfoCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class OneKeyDressResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const HERO:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoHero.OneKeyDressResp.hero", "hero", (1 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoHero.HeroBaseInfoCPP; });

		public var hero:ProtoHero.HeroBaseInfoCPP;

		/**
		 *  @private
		 */
		public static const EQUIPWRAP:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("ProtoHero.OneKeyDressResp.equipwrap", "equipwrap", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoHero.EquipmentWrapCPP; });

		public var equipwrap:ProtoHero.EquipmentWrapCPP;

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.hero);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.equipwrap);
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var hero$count:uint = 0;
			var equipwrap$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (hero$count != 0) {
						throw new flash.errors.IOError('Bad data format: OneKeyDressResp.hero cannot be set twice.');
					}
					++hero$count;
					this.hero = new ProtoHero.HeroBaseInfoCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.hero);
					break;
				case 2:
					if (equipwrap$count != 0) {
						throw new flash.errors.IOError('Bad data format: OneKeyDressResp.equipwrap cannot be set twice.');
					}
					++equipwrap$count;
					this.equipwrap = new ProtoHero.EquipmentWrapCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.equipwrap);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
