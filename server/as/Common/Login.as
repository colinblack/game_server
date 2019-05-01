package Common {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class Login extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const UID:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Common.Login.uid", "uid", (1 << 3) | com.netease.protobuf.WireType.VARINT);

		public var uid:uint;

		/**
		 *  @private
		 */
		public static const OPENKEY:FieldDescriptor_TYPE_STRING = new FieldDescriptor_TYPE_STRING("Common.Login.openkey", "openkey", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var openkey:String;

		/**
		 *  @private
		 */
		public static const TS:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Common.Login.ts", "ts", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		public var ts:uint;

		/**
		 *  @private
		 */
		public static const SIG:FieldDescriptor_TYPE_STRING = new FieldDescriptor_TYPE_STRING("Common.Login.sig", "sig", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		public var sig:String;

		/**
		 *  @private
		 */
		public static const FIG:FieldDescriptor_TYPE_STRING = new FieldDescriptor_TYPE_STRING("Common.Login.fig", "fig", (5 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		private var fig$field:String;

		public function clearFig():void {
			fig$field = null;
		}

		public function get hasFig():Boolean {
			return fig$field != null;
		}

		public function set fig(value:String):void {
			fig$field = value;
		}

		public function get fig():String {
			return fig$field;
		}

		/**
		 *  @private
		 */
		public static const ISNEW:FieldDescriptor_TYPE_BOOL = new FieldDescriptor_TYPE_BOOL("Common.Login.isnew", "isnew", (6 << 3) | com.netease.protobuf.WireType.VARINT);

		public var isnew:Boolean;

		/**
		 *  @private
		 */
		public static const KINGDOM:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Common.Login.kingdom", "kingdom", (7 << 3) | com.netease.protobuf.WireType.VARINT);

		public var kingdom:uint;

		/**
		 *  @private
		 */
		public static const PLATFORM:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Common.Login.platform", "platform", (8 << 3) | com.netease.protobuf.WireType.VARINT);

		public var platform:uint;

		/**
		 *  @private
		 */
		public static const TTSS_LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Common.Login.ttss_level", "ttssLevel", (9 << 3) | com.netease.protobuf.WireType.VARINT);

		private var ttss_level$field:uint;

		private var hasField$0:uint = 0;

		public function clearTtssLevel():void {
			hasField$0 &= 0xfffffffe;
			ttss_level$field = new uint();
		}

		public function get hasTtssLevel():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set ttssLevel(value:uint):void {
			hasField$0 |= 0x1;
			ttss_level$field = value;
		}

		public function get ttssLevel():uint {
			return ttss_level$field;
		}

		/**
		 *  @private
		 */
		public static const TTSS_LEVEL_NAME:FieldDescriptor_TYPE_STRING = new FieldDescriptor_TYPE_STRING("Common.Login.ttss_level_name", "ttssLevelName", (10 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		private var ttss_level_name$field:String;

		public function clearTtssLevelName():void {
			ttss_level_name$field = null;
		}

		public function get hasTtssLevelName():Boolean {
			return ttss_level_name$field != null;
		}

		public function set ttssLevelName(value:String):void {
			ttss_level_name$field = value;
		}

		public function get ttssLevelName():String {
			return ttss_level_name$field;
		}

		/**
		 *  @private
		 */
		public static const TTSS_GROW_LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Common.Login.ttss_grow_level", "ttssGrowLevel", (11 << 3) | com.netease.protobuf.WireType.VARINT);

		private var ttss_grow_level$field:uint;

		public function clearTtssGrowLevel():void {
			hasField$0 &= 0xfffffffd;
			ttss_grow_level$field = new uint();
		}

		public function get hasTtssGrowLevel():Boolean {
			return (hasField$0 & 0x2) != 0;
		}

		public function set ttssGrowLevel(value:uint):void {
			hasField$0 |= 0x2;
			ttss_grow_level$field = value;
		}

		public function get ttssGrowLevel():uint {
			return ttss_grow_level$field;
		}

		/**
		 *  @private
		 */
		public static const TTSS_GROW_VALUE:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Common.Login.ttss_grow_value", "ttssGrowValue", (12 << 3) | com.netease.protobuf.WireType.VARINT);

		private var ttss_grow_value$field:uint;

		public function clearTtssGrowValue():void {
			hasField$0 &= 0xfffffffb;
			ttss_grow_value$field = new uint();
		}

		public function get hasTtssGrowValue():Boolean {
			return (hasField$0 & 0x4) != 0;
		}

		public function set ttssGrowValue(value:uint):void {
			hasField$0 |= 0x4;
			ttss_grow_value$field = value;
		}

		public function get ttssGrowValue():uint {
			return ttss_grow_value$field;
		}

		/**
		 *  @private
		 */
		public static const IS_BLUE_VIP:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Common.Login.is_blue_vip", "isBlueVip", (13 << 3) | com.netease.protobuf.WireType.VARINT);

		private var is_blue_vip$field:uint;

		public function clearIsBlueVip():void {
			hasField$0 &= 0xfffffff7;
			is_blue_vip$field = new uint();
		}

		public function get hasIsBlueVip():Boolean {
			return (hasField$0 & 0x8) != 0;
		}

		public function set isBlueVip(value:uint):void {
			hasField$0 |= 0x8;
			is_blue_vip$field = value;
		}

		public function get isBlueVip():uint {
			return is_blue_vip$field;
		}

		/**
		 *  @private
		 */
		public static const IS_BLUE_YEAR_VIP:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Common.Login.is_blue_year_vip", "isBlueYearVip", (14 << 3) | com.netease.protobuf.WireType.VARINT);

		private var is_blue_year_vip$field:uint;

		public function clearIsBlueYearVip():void {
			hasField$0 &= 0xffffffef;
			is_blue_year_vip$field = new uint();
		}

		public function get hasIsBlueYearVip():Boolean {
			return (hasField$0 & 0x10) != 0;
		}

		public function set isBlueYearVip(value:uint):void {
			hasField$0 |= 0x10;
			is_blue_year_vip$field = value;
		}

		public function get isBlueYearVip():uint {
			return is_blue_year_vip$field;
		}

		/**
		 *  @private
		 */
		public static const IS_SUPER_BLUE_VIP:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Common.Login.is_super_blue_vip", "isSuperBlueVip", (15 << 3) | com.netease.protobuf.WireType.VARINT);

		private var is_super_blue_vip$field:uint;

		public function clearIsSuperBlueVip():void {
			hasField$0 &= 0xffffffdf;
			is_super_blue_vip$field = new uint();
		}

		public function get hasIsSuperBlueVip():Boolean {
			return (hasField$0 & 0x20) != 0;
		}

		public function set isSuperBlueVip(value:uint):void {
			hasField$0 |= 0x20;
			is_super_blue_vip$field = value;
		}

		public function get isSuperBlueVip():uint {
			return is_super_blue_vip$field;
		}

		/**
		 *  @private
		 */
		public static const BLUE_VIP_LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Common.Login.blue_vip_level", "blueVipLevel", (16 << 3) | com.netease.protobuf.WireType.VARINT);

		private var blue_vip_level$field:uint;

		public function clearBlueVipLevel():void {
			hasField$0 &= 0xffffffbf;
			blue_vip_level$field = new uint();
		}

		public function get hasBlueVipLevel():Boolean {
			return (hasField$0 & 0x40) != 0;
		}

		public function set blueVipLevel(value:uint):void {
			hasField$0 |= 0x40;
			blue_vip_level$field = value;
		}

		public function get blueVipLevel():uint {
			return blue_vip_level$field;
		}

		/**
		 *  @private
		 */
		public static const IS_YELLOW_VIP:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Common.Login.is_yellow_vip", "isYellowVip", (17 << 3) | com.netease.protobuf.WireType.VARINT);

		private var is_yellow_vip$field:uint;

		public function clearIsYellowVip():void {
			hasField$0 &= 0xffffff7f;
			is_yellow_vip$field = new uint();
		}

		public function get hasIsYellowVip():Boolean {
			return (hasField$0 & 0x80) != 0;
		}

		public function set isYellowVip(value:uint):void {
			hasField$0 |= 0x80;
			is_yellow_vip$field = value;
		}

		public function get isYellowVip():uint {
			return is_yellow_vip$field;
		}

		/**
		 *  @private
		 */
		public static const IS_YELLOW_YEAR_VIP:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Common.Login.is_yellow_year_vip", "isYellowYearVip", (18 << 3) | com.netease.protobuf.WireType.VARINT);

		private var is_yellow_year_vip$field:uint;

		public function clearIsYellowYearVip():void {
			hasField$0 &= 0xfffffeff;
			is_yellow_year_vip$field = new uint();
		}

		public function get hasIsYellowYearVip():Boolean {
			return (hasField$0 & 0x100) != 0;
		}

		public function set isYellowYearVip(value:uint):void {
			hasField$0 |= 0x100;
			is_yellow_year_vip$field = value;
		}

		public function get isYellowYearVip():uint {
			return is_yellow_year_vip$field;
		}

		/**
		 *  @private
		 */
		public static const YELLOW_VIP_LEVEL:FieldDescriptor_TYPE_UINT32 = new FieldDescriptor_TYPE_UINT32("Common.Login.yellow_vip_level", "yellowVipLevel", (19 << 3) | com.netease.protobuf.WireType.VARINT);

		private var yellow_vip_level$field:uint;

		public function clearYellowVipLevel():void {
			hasField$0 &= 0xfffffdff;
			yellow_vip_level$field = new uint();
		}

		public function get hasYellowVipLevel():Boolean {
			return (hasField$0 & 0x200) != 0;
		}

		public function set yellowVipLevel(value:uint):void {
			hasField$0 |= 0x200;
			yellow_vip_level$field = value;
		}

		public function get yellowVipLevel():uint {
			return yellow_vip_level$field;
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.uid);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
			com.netease.protobuf.WriteUtils.write_TYPE_STRING(output, this.openkey);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.ts);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
			com.netease.protobuf.WriteUtils.write_TYPE_STRING(output, this.sig);
			if (hasFig) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 5);
				com.netease.protobuf.WriteUtils.write_TYPE_STRING(output, fig$field);
			}
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 6);
			com.netease.protobuf.WriteUtils.write_TYPE_BOOL(output, this.isnew);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 7);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.kingdom);
			com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 8);
			com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, this.platform);
			if (hasTtssLevel) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 9);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, ttss_level$field);
			}
			if (hasTtssLevelName) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 10);
				com.netease.protobuf.WriteUtils.write_TYPE_STRING(output, ttss_level_name$field);
			}
			if (hasTtssGrowLevel) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 11);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, ttss_grow_level$field);
			}
			if (hasTtssGrowValue) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 12);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, ttss_grow_value$field);
			}
			if (hasIsBlueVip) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 13);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, is_blue_vip$field);
			}
			if (hasIsBlueYearVip) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 14);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, is_blue_year_vip$field);
			}
			if (hasIsSuperBlueVip) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 15);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, is_super_blue_vip$field);
			}
			if (hasBlueVipLevel) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 16);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, blue_vip_level$field);
			}
			if (hasIsYellowVip) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 17);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, is_yellow_vip$field);
			}
			if (hasIsYellowYearVip) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 18);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, is_yellow_year_vip$field);
			}
			if (hasYellowVipLevel) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 19);
				com.netease.protobuf.WriteUtils.write_TYPE_UINT32(output, yellow_vip_level$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override com.netease.protobuf.used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var uid$count:uint = 0;
			var openkey$count:uint = 0;
			var ts$count:uint = 0;
			var sig$count:uint = 0;
			var fig$count:uint = 0;
			var isnew$count:uint = 0;
			var kingdom$count:uint = 0;
			var platform$count:uint = 0;
			var ttss_level$count:uint = 0;
			var ttss_level_name$count:uint = 0;
			var ttss_grow_level$count:uint = 0;
			var ttss_grow_value$count:uint = 0;
			var is_blue_vip$count:uint = 0;
			var is_blue_year_vip$count:uint = 0;
			var is_super_blue_vip$count:uint = 0;
			var blue_vip_level$count:uint = 0;
			var is_yellow_vip$count:uint = 0;
			var is_yellow_year_vip$count:uint = 0;
			var yellow_vip_level$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (uid$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.uid cannot be set twice.');
					}
					++uid$count;
					this.uid = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 2:
					if (openkey$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.openkey cannot be set twice.');
					}
					++openkey$count;
					this.openkey = com.netease.protobuf.ReadUtils.read_TYPE_STRING(input);
					break;
				case 3:
					if (ts$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.ts cannot be set twice.');
					}
					++ts$count;
					this.ts = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 4:
					if (sig$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.sig cannot be set twice.');
					}
					++sig$count;
					this.sig = com.netease.protobuf.ReadUtils.read_TYPE_STRING(input);
					break;
				case 5:
					if (fig$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.fig cannot be set twice.');
					}
					++fig$count;
					this.fig = com.netease.protobuf.ReadUtils.read_TYPE_STRING(input);
					break;
				case 6:
					if (isnew$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.isnew cannot be set twice.');
					}
					++isnew$count;
					this.isnew = com.netease.protobuf.ReadUtils.read_TYPE_BOOL(input);
					break;
				case 7:
					if (kingdom$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.kingdom cannot be set twice.');
					}
					++kingdom$count;
					this.kingdom = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 8:
					if (platform$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.platform cannot be set twice.');
					}
					++platform$count;
					this.platform = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 9:
					if (ttss_level$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.ttssLevel cannot be set twice.');
					}
					++ttss_level$count;
					this.ttssLevel = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 10:
					if (ttss_level_name$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.ttssLevelName cannot be set twice.');
					}
					++ttss_level_name$count;
					this.ttssLevelName = com.netease.protobuf.ReadUtils.read_TYPE_STRING(input);
					break;
				case 11:
					if (ttss_grow_level$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.ttssGrowLevel cannot be set twice.');
					}
					++ttss_grow_level$count;
					this.ttssGrowLevel = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 12:
					if (ttss_grow_value$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.ttssGrowValue cannot be set twice.');
					}
					++ttss_grow_value$count;
					this.ttssGrowValue = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 13:
					if (is_blue_vip$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.isBlueVip cannot be set twice.');
					}
					++is_blue_vip$count;
					this.isBlueVip = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 14:
					if (is_blue_year_vip$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.isBlueYearVip cannot be set twice.');
					}
					++is_blue_year_vip$count;
					this.isBlueYearVip = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 15:
					if (is_super_blue_vip$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.isSuperBlueVip cannot be set twice.');
					}
					++is_super_blue_vip$count;
					this.isSuperBlueVip = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 16:
					if (blue_vip_level$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.blueVipLevel cannot be set twice.');
					}
					++blue_vip_level$count;
					this.blueVipLevel = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 17:
					if (is_yellow_vip$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.isYellowVip cannot be set twice.');
					}
					++is_yellow_vip$count;
					this.isYellowVip = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 18:
					if (is_yellow_year_vip$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.isYellowYearVip cannot be set twice.');
					}
					++is_yellow_year_vip$count;
					this.isYellowYearVip = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				case 19:
					if (yellow_vip_level$count != 0) {
						throw new flash.errors.IOError('Bad data format: Login.yellowVipLevel cannot be set twice.');
					}
					++yellow_vip_level$count;
					this.yellowVipLevel = com.netease.protobuf.ReadUtils.read_TYPE_UINT32(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
