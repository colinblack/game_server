package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSMartialHeroInfo
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoCSMartialHeroInfo";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var attr:Vector.<HeroBaseInfoCPP>;
		public function ProtoCSMartialHeroInfo(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			uid = undefined;
			attr = new Vector.<HeroBaseInfoCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.attr = [];
			for(var i:int = 0;i < this.attr.length;i++)
			{
				serializeObj.attr.push(this.attr[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSMartialHeroInfo
		{
			uid = undefined;
			attr = new Vector.<HeroBaseInfoCPP>();
			this.uid = msgObj.uid;
			for(var i:int = 0;i < msgObj.attr.length;i++)
			{
				this.attr.push(new HeroBaseInfoCPP(package_root).unserialize(msgObj.attr[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSMartialHeroInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}