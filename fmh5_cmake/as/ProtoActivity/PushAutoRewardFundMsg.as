package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class PushAutoRewardFundMsg
	{
		public static const PROTO:String = "ProtoActivity.PushAutoRewardFundMsg";
		public var package_root:*;
		public  var message:*;
		public var commons:Vector.<CommonItemsCPP>;
		public function PushAutoRewardFundMsg(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = new Vector.<CommonItemsCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = [];
			for(var i:int = 0;i < this.commons.length;i++)
			{
				serializeObj.commons.push(this.commons[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushAutoRewardFundMsg
		{
			commons = new Vector.<CommonItemsCPP>();
			for(var i:int = 0;i < msgObj.commons.length;i++)
			{
				this.commons.push(new CommonItemsCPP(package_root).unserialize(msgObj.commons[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushAutoRewardFundMsg
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}