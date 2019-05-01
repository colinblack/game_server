package User {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import ProtoHero.HeroBaseInfoCPP;
	import DataCommon.EquipmentCPP;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class UseUpdateSmeltPropResp extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const PROP_UD:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.UseUpdateSmeltPropResp.prop_ud", "propUd", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var propUd:uint;

		/**
		 *  @private
		 */
		public static const PROP_CNT:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("User.UseUpdateSmeltPropResp.prop_cnt", "propCnt", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		public var propCnt:uint;

		/**
		 *  @private
		 */
		public static const EQUIP:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.UseUpdateSmeltPropResp.equip", "equip", (3 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return DataCommon.EquipmentCPP; });

		public var equip:DataCommon.EquipmentCPP;

		/**
		 *  @private
		 */
		public static const HERO:FieldDescriptor_TYPE_MESSAGE = new FieldDescriptor_TYPE_MESSAGE("User.UseUpdateSmeltPropResp.hero", "hero", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED, function():Class { return ProtoHero.HeroBaseInfoCPP; });

		private var hero$field:ProtoHero.HeroBaseInfoCPP;

		public function clearHero():void {
			hero$field = null;
		}

		public function get hasHero():Boolean {
			return hero$field != null;
		}

		public function set hero(value:ProtoHero.HeroBaseInfoCPP):void {
			hero$field = value;
		}

		public function get hero():ProtoHero.HeroBaseInfoCPP {
			return hero$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.propUd);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.propCnt);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, this.equip);
			if (hasHero) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
				com.netease.protobuf.WriteUtils.write_TYPE_MESSAGE(output, hero$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var prop_ud$count:uint = 0;
			var prop_cnt$count:uint = 0;
			var equip$count:uint = 0;
			var hero$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (prop_ud$count != 0) {
						throw new flash.errors.IOError('Bad data format: UseUpdateSmeltPropResp.propUd cannot be set twice.');
					}
					++prop_ud$count;
					this.propUd = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (prop_cnt$count != 0) {
						throw new flash.errors.IOError('Bad data format: UseUpdateSmeltPropResp.propCnt cannot be set twice.');
					}
					++prop_cnt$count;
					this.propCnt = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 3:
					if (equip$count != 0) {
						throw new flash.errors.IOError('Bad data format: UseUpdateSmeltPropResp.equip cannot be set twice.');
					}
					++equip$count;
					this.equip = new DataCommon.EquipmentCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.equip);
					break;
				case 4:
					if (hero$count != 0) {
						throw new flash.errors.IOError('Bad data format: UseUpdateSmeltPropResp.hero cannot be set twice.');
					}
					++hero$count;
					this.hero = new ProtoHero.HeroBaseInfoCPP();
					com.netease.protobuf.ReadUtils.read_TYPE_MESSAGE(input, this.hero);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
