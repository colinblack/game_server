package com.sanguo.game.server.connectlogic.common.message.DataCommon
{
	import laya.utils.Byte;
	public class UserBaseChangeCPP
	{
		public static const PROTO:String = "DataCommon.UserBaseChangeCPP";
		public var package_root:*;
		public  var message:*;
		public var baseItem:Vector.<BaseItemCPP>;
		public function UserBaseChangeCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			baseItem = new Vector.<BaseItemCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.baseItem = [];
			for(var i:int = 0;i < this.baseItem.length;i++)
			{
				serializeObj.baseItem.push(this.baseItem[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):UserBaseChangeCPP
		{
			baseItem = new Vector.<BaseItemCPP>();
			for(var i:int = 0;i < msgObj.baseItem.length;i++)
			{
				this.baseItem.push(new BaseItemCPP(package_root).unserialize(msgObj.baseItem[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UserBaseChangeCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}