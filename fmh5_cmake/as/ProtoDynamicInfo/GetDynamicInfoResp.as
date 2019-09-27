package com.sanguo.game.server.connectlogic.common.message.ProtoDynamicInfo
{
	import laya.utils.Byte;
	public class GetDynamicInfoResp
	{
		public static const PROTO:String = "ProtoDynamicInfo.GetDynamicInfoResp";
		public var package_root:*;
		public  var message:*;
		public var arrayDyInfo:Vector.<DynamicInfo>;
		public function GetDynamicInfoResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			arrayDyInfo = new Vector.<DynamicInfo>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.arrayDyInfo = [];
			for(var i:int = 0;i < this.arrayDyInfo.length;i++)
			{
				serializeObj.arrayDyInfo.push(this.arrayDyInfo[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetDynamicInfoResp
		{
			arrayDyInfo = new Vector.<DynamicInfo>();
			for(var i:int = 0;i < msgObj.arrayDyInfo.length;i++)
			{
				this.arrayDyInfo.push(new DynamicInfo(package_root).unserialize(msgObj.arrayDyInfo[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetDynamicInfoResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}