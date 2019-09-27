package com.sanguo.game.server.connectlogic.common.message.DataCommon
{
	import laya.utils.Byte;
	public class PropsAllChangeCPP
	{
		public static const PROTO:String = "DataCommon.PropsAllChangeCPP";
		public var package_root:*;
		public  var message:*;
		public var propsitem:Vector.<PropsChangeCPP>;
		public function PropsAllChangeCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			propsitem = new Vector.<PropsChangeCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.propsitem = [];
			for(var i:int = 0;i < this.propsitem.length;i++)
			{
				serializeObj.propsitem.push(this.propsitem[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):PropsAllChangeCPP
		{
			propsitem = new Vector.<PropsChangeCPP>();
			for(var i:int = 0;i < msgObj.propsitem.length;i++)
			{
				this.propsitem.push(new PropsChangeCPP(package_root).unserialize(msgObj.propsitem[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PropsAllChangeCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}