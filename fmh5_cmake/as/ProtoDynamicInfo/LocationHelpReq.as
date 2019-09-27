package com.sanguo.game.server.connectlogic.common.message.ProtoDynamicInfo
{
	import laya.utils.Byte;
	public class LocationHelpReq
	{
		public static const PROTO:String = "ProtoDynamicInfo.LocationHelpReq";
		public var package_root:*;
		public  var message:*;
		public var typeid:int;
		public var arrayuid:Vector.<int>;
		public function LocationHelpReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			typeid = undefined;
			arrayuid = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.typeid = this.typeid;
			serializeObj.arrayuid = [];
			for(var i:int = 0;i < this.arrayuid.length;i++)
			{
				serializeObj.arrayuid.push(this.arrayuid[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):LocationHelpReq
		{
			typeid = undefined;
			arrayuid = new Vector.<int>();
			this.typeid = msgObj.typeid;
			for(var i:int = 0;i < msgObj.arrayuid.length;i++)
			{
				this.arrayuid.push(msgObj.arrayuid[i]);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):LocationHelpReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}