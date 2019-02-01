package com.sanguo.game.server.connectlogic.common.message.ProtoNotify
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class MartialClubItemCpp
	{
		public static const PROTO:String = "ProtoNotify.MartialClubItemCpp";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var type:int;
		public var ts:int;
		public var uid:int;
		public var name:String;
		public var level:int;
		public var fig:String;
		public var grade:int;
		public var slot:int;
		public var win:int;
		public var coin:int;
		public var props:Vector.<PropsItemCpp>;
		public function MartialClubItemCpp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			id = undefined;
			type = undefined;
			ts = undefined;
			uid = undefined;
			name = undefined;
			level = undefined;
			fig = undefined;
			grade = undefined;
			slot = undefined;
			win = undefined;
			coin = undefined;
			props = new Vector.<PropsItemCpp>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.type = this.type;
			serializeObj.ts = this.ts;
			serializeObj.uid = this.uid;
			serializeObj.name = this.name;
			serializeObj.level = this.level;
			serializeObj.fig = this.fig;
			serializeObj.grade = this.grade;
			if(this.slot!= undefined)
			{
				serializeObj.slot = this.slot;
			}
			if(this.win!= undefined)
			{
				serializeObj.win = this.win;
			}
			if(this.coin!= undefined)
			{
				serializeObj.coin = this.coin;
			}
			serializeObj.props = [];
			for(var i:int = 0;i < this.props.length;i++)
			{
				serializeObj.props.push(this.props[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):MartialClubItemCpp
		{
			id = undefined;
			type = undefined;
			ts = undefined;
			uid = undefined;
			name = undefined;
			level = undefined;
			fig = undefined;
			grade = undefined;
			slot = undefined;
			win = undefined;
			coin = undefined;
			props = new Vector.<PropsItemCpp>();
			this.id = msgObj.id;
			this.type = msgObj.type;
			this.ts = msgObj.ts;
			this.uid = msgObj.uid;
			this.name = msgObj.name;
			this.level = msgObj.level;
			this.fig = msgObj.fig;
			this.grade = msgObj.grade;
			if(msgObj.hasOwnProperty("slot"))
			{
				this.slot = msgObj.slot;
			}
			if(msgObj.hasOwnProperty("win"))
			{
				this.win = msgObj.win;
			}
			if(msgObj.hasOwnProperty("coin"))
			{
				this.coin = msgObj.coin;
			}
			for(var i:int = 0;i < msgObj.props.length;i++)
			{
				this.props.push(new PropsItemCpp(package_root).unserialize(msgObj.props[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):MartialClubItemCpp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}